TupleQueueFunnelNext(TupleQueueFunnel *funnel, bool nowait, bool *done)
{
	int			waitpos = funnel->nextqueue;


	if (funnel->nqueues == 0)
	{
		if (done != NULL)
			*done = true;
		return NULL;
	}

	if (done != NULL)
		*done = false;

	for (;;)
	{
		shm_mq_handle *mqh = funnel->queue[funnel->nextqueue];
		shm_mq_result result;
		Size		nbytes;
		void	   *data;


		result = shm_mq_receive(mqh, &nbytes, &data, true);


		if (result != SHM_MQ_DETACHED)
			funnel->nextqueue = (funnel->nextqueue + 1) % funnel->nqueues;
		else
		{
			--funnel->nqueues;
			if (funnel->nqueues == 0)
			{
				if (done != NULL)
					*done = true;
				return NULL;
			}

			memmove(&funnel->queue[funnel->nextqueue],
					&funnel->queue[funnel->nextqueue + 1],
					sizeof(shm_mq_handle *)
					* (funnel->nqueues - funnel->nextqueue));

			if (funnel->nextqueue >= funnel->nqueues)
				funnel->nextqueue = 0;

			if (funnel->nextqueue < waitpos)
				--waitpos;

			continue;
		}


		if (result == SHM_MQ_SUCCESS)
		{
			HeapTupleData htup;


			ItemPointerSetInvalid(&htup.t_self);
			htup.t_tableOid = InvalidOid;
			htup.t_len = nbytes;
			htup.t_data = data;
			return heap_copytuple(&htup);
		}


		if (funnel->nextqueue == waitpos)
		{
			if (nowait)
				return NULL;
			WaitLatch(MyLatch, WL_LATCH_SET, 0);
			CHECK_FOR_INTERRUPTS();
			ResetLatch(MyLatch);
		}
	}
}

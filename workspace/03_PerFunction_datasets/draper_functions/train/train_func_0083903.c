postquel_end(execution_state *es)
{

	es->status = F_EXEC_DONE;


	if (es->qd->utilitystmt == NULL)
	{
		ExecutorFinish(es->qd);
		ExecutorEnd(es->qd);
	}

	(*es->qd->dest->rDestroy) (es->qd->dest);

	FreeQueryDesc(es->qd);
	es->qd = NULL;
}

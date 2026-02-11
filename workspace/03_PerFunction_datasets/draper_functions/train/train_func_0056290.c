thread_loop(WORKER_INFO *info, char *errbuf, ESL_THREADS *obj, ESL_WORK_QUEUE *queue, ESL_SQ_BLOCK *sq_block)
{
  int      status = eslOK;
  int      i, k;
  ESL_SQ  *sq;
  void    *new_sq;
  ESL_SQ  *empty_sq;
  int      nworkers = esl_threads_GetWorkerCount(obj);

  esl_workqueue_Reset(queue);
#if DEBUGSERIAL
  printf("master threads reset\n");
#endif

  esl_threads_WaitForStart(obj);

#if DEBUGSERIAL
  printf("master threads started\n");
#endif

  status = esl_workqueue_ReaderUpdate(queue, NULL, &new_sq);
  if (status != eslOK) cm_Fail("Work queue reader failed");

#if DEBUGSERIAL
  printf("master initial update\n");
#endif


  for(i = 0; i < sq_block->count; i++) {
    sq    = (ESL_SQ *) new_sq;
    sq    = sq_block->list + i;
    sq->W = sq_block->first_seqidx + i;

    status = esl_workqueue_ReaderUpdate(queue, sq, &new_sq);
    if (status != eslOK) cm_Fail("Work queue reader failed");

#if DEBUGSERIAL
    printf("master internal update\n");
#endif
  }


  empty_sq = esl_sq_Create();
  for(k = 0; k < nworkers; k++) {
    status = esl_workqueue_ReaderUpdate(queue, empty_sq, &new_sq);
    if (status != eslOK) cm_Fail("Work queue reader failed");
#if DEBUGSERIAL
    printf("master termination update\n");
#endif
  }

  status = esl_workqueue_ReaderUpdate(queue, sq, NULL);
#if DEBUGSERIAL
  printf("master final update\n");
#endif


  esl_threads_WaitForFinish(obj);
#if DEBUGSERIAL
  printf("master got finish\n");
#endif

  esl_workqueue_Complete(queue);
#if DEBUGSERIAL
  printf("master completed\n");
#endif

  esl_sq_Destroy(empty_sq);
  return status;
}

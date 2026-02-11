serialize(struct sftpjob *job) {
  struct sqnode *q, *oq;

  ferrcheck(pthread_mutex_lock(&sq_mutex));
  for(;;) {
    for(q = newest; q && q->job != job; q = q->older)
      ;


    if(!q)
      break;


    for(oq = q->older; oq; oq = oq->older)
      if(!reorderable(q, oq, q->handleflags))
        break;
    if(!oq)
      break;

    ferrcheck(pthread_cond_wait(&sq_cond, &sq_mutex));
  }

  ferrcheck(pthread_mutex_unlock(&sq_mutex));
}

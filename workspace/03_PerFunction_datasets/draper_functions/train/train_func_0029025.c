semaphore_test()
{
  OFString errmsg;
  mutex = new OFMutex();
  if ((!mutex)||(! mutex->initialized())) bailout("creation of mutex failed", __LINE__);
  semaphore = new OFSemaphore(2);
  if ((!semaphore)||(! semaphore->initialized())) bailout("creation of semaphore failed", __LINE__);
  int condition = mutex->trylock();
  if (condition)
  {
    mutex->errorstr(errmsg, condition);
    CERR << "mutex lock failed: ";
    bailout(errmsg.c_str(), __LINE__);
  }
  condition = semaphore->trywait();
  if (condition)
  {
    semaphore->errorstr(errmsg, condition);
    CERR << "semaphore acquisition failed: ";
    bailout(errmsg.c_str(), __LINE__);
  }

  SemaT1 t1;
  if (0 != t1.start()) bailout("unable to create thread, semaphore test failed", __LINE__);

  SemaT2 t2;
  if (0 != t2.start()) bailout("unable to create thread, semaphore test failed", __LINE__);

  int i=0;
  while ((i++<5) && (!sem_cond1)) OFStandard::sleep(1);
  if (!sem_cond1) bailout("semaphore lock/unlock test failed", __LINE__);
  OFStandard::sleep(1);
  if (sem_cond3) bailout("semaphore lock/unlock test failed", __LINE__);
  mutex->unlock();

  i=0;
  while ((i++<5) && ((!sem_cond2)||(!sem_cond3)||(!sem_cond4))) OFStandard::sleep(1);
  if ((!mtx_cond2) || (!mtx_cond3) || (!sem_cond4)) bailout("semaphore lock/unlock test failed", __LINE__);

  delete mutex;
  delete semaphore;
  CERR << "semaphore test passed." << OFendl;
}

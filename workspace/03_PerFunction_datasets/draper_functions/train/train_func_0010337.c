test_atomic_cas(void *arg)
{
  int m= (*(int *)arg)/2, ok= 0;
  int32 x, y;
  for (x= ((int)(intptr)(&m)); m ; m--)
  {
    my_atomic_rwlock_wrlock(&rwl);
    y= my_atomic_load32(&bad);
    my_atomic_rwlock_wrunlock(&rwl);
    x= (x*m+0x87654321) & INT_MAX32;
    do {
      my_atomic_rwlock_wrlock(&rwl);
      ok= my_atomic_cas32(&bad, &y, (uint32)y+x);
      my_atomic_rwlock_wrunlock(&rwl);
    } while (!ok) ;
    do {
      my_atomic_rwlock_wrlock(&rwl);
      ok= my_atomic_cas32(&bad, &y, y-x);
      my_atomic_rwlock_wrunlock(&rwl);
    } while (!ok) ;
  }
  pthread_mutex_lock(&mutex);
  if (!--running_threads) pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  return 0;
}

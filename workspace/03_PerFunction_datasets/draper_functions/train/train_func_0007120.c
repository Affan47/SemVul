thr_abort_locks(THR_LOCK *lock, my_bool upgrade_lock)
{
  THR_LOCK_DATA *data;
  DBUG_ENTER("thr_abort_locks");
  mysql_mutex_lock(&lock->mutex);

  for (data=lock->read_wait.data; data ; data=data->next)
  {
    data->type=TL_UNLOCK;

    mysql_cond_signal(data->cond);
    data->cond=0;
  }
  for (data=lock->write_wait.data; data ; data=data->next)
  {
    data->type=TL_UNLOCK;
    mysql_cond_signal(data->cond);
    data->cond=0;
  }
  lock->read_wait.last= &lock->read_wait.data;
  lock->write_wait.last= &lock->write_wait.data;
  lock->read_wait.data=lock->write_wait.data=0;
  if (upgrade_lock && lock->write.data)
    lock->write.data->type=TL_WRITE_ONLY;
  mysql_mutex_unlock(&lock->mutex);
  DBUG_VOID_RETURN;
}

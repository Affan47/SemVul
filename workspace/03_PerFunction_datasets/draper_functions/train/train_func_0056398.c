take_lock(take_lock_t *hold, int areason)
{
   int stat;

   if (valid != DEVLOCK_VALID) {
      return EINVAL;
   }
   if ((stat = pthread_mutex_lock(&mutex)) != 0) {
      return stat;
   }
   hold->reason = reason;
   hold->prev_reason = prev_reason;
   hold->writer_id = writer_id;
   reason = areason;
   writer_id = pthread_self();
   stat = pthread_mutex_unlock(&mutex);
   return stat;
}

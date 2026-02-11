init(int priority)
{
   int stat;
   devlock *rwl = this;

   rwl->r_active = rwl->w_active = 0;
   rwl->r_wait = rwl->w_wait = 0;
   rwl->priority = priority;
   if ((stat = pthread_mutex_init(&rwl->mutex, NULL)) != 0) {
      return stat;
   }
   if ((stat = pthread_cond_init(&rwl->read, NULL)) != 0) {
      pthread_mutex_destroy(&rwl->mutex);
      return stat;
   }
   if ((stat = pthread_cond_init(&rwl->write, NULL)) != 0) {
      pthread_cond_destroy(&rwl->read);
      pthread_mutex_destroy(&rwl->mutex);
      return stat;
   }
   rwl->valid = DEVLOCK_VALID;
   return 0;
}

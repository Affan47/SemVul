destroy()
{
   devlock *rwl = this;
   int stat, stat1, stat2;

   if (rwl->valid != DEVLOCK_VALID) {
      return EINVAL;
   }
   if ((stat = pthread_mutex_lock(&rwl->mutex)) != 0) {
      return stat;
   }


   if (rwl->r_active > 0 || rwl->w_active) {
      pthread_mutex_unlock(&rwl->mutex);
      return EBUSY;
   }


   if (rwl->r_wait > 0 || rwl->w_wait > 0) {
      pthread_mutex_unlock(&rwl->mutex);
      return EBUSY;
   }

   rwl->valid = 0;
   if ((stat = pthread_mutex_unlock(&rwl->mutex)) != 0) {
      return stat;
   }
   stat  = pthread_mutex_destroy(&rwl->mutex);
   stat1 = pthread_cond_destroy(&rwl->read);
   stat2 = pthread_cond_destroy(&rwl->write);
   return (stat != 0 ? stat : (stat1 != 0 ? stat1 : stat2));
}

_eina_log_spinlock_init(void)
{
   if (pthread_spin_init(&_log_lock, PTHREAD_PROCESS_PRIVATE) == 0)
     return EINA_TRUE;

   fprintf(stderr,
           "ERROR: pthread_spin_init(%p, PTHREAD_PROCESS_PRIVATE): %s\n",
           &_log_lock, strerror(errno));
   return EINA_FALSE;
}

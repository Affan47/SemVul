openssl_init_threads (void)
{
   int i, numlocks;
   int stat;


   CRYPTO_set_id_callback(get_openssl_thread_id);


   numlocks = CRYPTO_num_locks();
   mutexes = (pthread_mutex_t *) malloc(numlocks * sizeof(pthread_mutex_t));
   for (i = 0; i < numlocks; i++) {
      if ((stat = pthread_mutex_init(&mutexes[i], NULL)) != 0) {
         berrno be;
         Jmsg1(NULL, M_FATAL, 0, _("Unable to init mutex: ERR=%s\n"), be.bstrerror(stat));
         return stat;
      }
   }


   CRYPTO_set_locking_callback(openssl_update_static_mutex);


   CRYPTO_set_dynlock_create_callback(openssl_create_dynamic_mutex);
   CRYPTO_set_dynlock_lock_callback(openssl_update_dynamic_mutex);
   CRYPTO_set_dynlock_destroy_callback(openssl_destroy_dynamic_mutex);

   return 0;
}

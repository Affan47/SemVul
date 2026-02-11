eina_file_shutdown(void)
{
   if (eina_hash_population(_eina_file_cache) > 0)
     {
        Eina_Iterator *it;
        const char *key;

        it = eina_hash_iterator_key_new(_eina_file_cache);
        EINA_ITERATOR_FOREACH(it, key)
          ERR("File [%s] still open !", key);
        eina_iterator_free(it);
     }

   eina_hash_free(_eina_file_cache);

   eina_lock_free(&_eina_file_lock_cache);

   eina_log_domain_unregister(_eina_file_log_dom);
   _eina_file_log_dom = -1;
   return EINA_TRUE;
}

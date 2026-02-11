eio_init(void)
{
   if (++_eio_init_count != 1)
     return _eio_init_count;

   if (!eina_init())
     {
        fprintf(stderr, "Eio can not initialize Eina\n");
        return --_eio_init_count;
     }

   _eio_log_dom_global = eina_log_domain_register("eio", EIO_DEFAULT_LOG_COLOR);
   if (_eio_log_dom_global < 0)
     {
        EINA_LOG_ERR("Eio can not create a general log domain.");
        goto shutdown_eina;
     }

   if (!ecore_init())
     {
        ERR("Can not initialize Eina\n");
        goto unregister_log_domain;
     }

   EIO_MUTEX_INIT(progress_pool);
   EIO_MUTEX_INIT(direct_info_pool);
   EIO_MUTEX_INIT(char_pool);
   EIO_MUTEX_INIT(associate_pool);

   eio_monitor_init();

   return _eio_init_count;

unregister_log_domain:
   eina_log_domain_unregister(_eio_log_dom_global);
   _eio_log_dom_global = -1;
shutdown_eina:
   eina_shutdown();
   return --_eio_init_count;
}

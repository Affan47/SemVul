ecore_evas_init(void)
{
   int fd;

   if (++_ecore_evas_init_count != 1)
     return _ecore_evas_init_count;

   if (!evas_init())
     return --_ecore_evas_init_count;

   if (!ecore_init())
     goto shutdown_evas;

   _ecore_evas_log_dom = eina_log_domain_register
     ("ecore_evas", ECORE_EVAS_DEFAULT_LOG_COLOR);
   if(_ecore_evas_log_dom < 0)
     {
        EINA_LOG_ERR("Impossible to create a log domain for Ecore_Evas.");
        goto shutdown_ecore;
     }

   ecore_fork_reset_callback_add(_ecore_evas_fork_cb, NULL);
   fd = evas_async_events_fd_get();
   if (fd >= 0)
     _ecore_evas_async_events_fd =
     ecore_main_fd_handler_add(fd, ECORE_FD_READ,
                               _ecore_evas_async_events_fd_handler, NULL,
                               NULL, NULL);

   ecore_evas_idle_enterer =
     ecore_idle_enterer_add(_ecore_evas_idle_enter, NULL);
   if (getenv("ECORE_EVAS_FPS_DEBUG")) _ecore_evas_fps_debug = 1;
   if (_ecore_evas_fps_debug) _ecore_evas_fps_debug_init();

#ifdef BUILD_ECORE_EVAS_EWS
   _ecore_evas_ews_events_init();
#endif

   _ecore_evas_extn_init();

   if (getenv("ECORE_EVAS_COMP_NOSYNC"))
      _ecore_evas_app_comp_sync = 0;
   return _ecore_evas_init_count;

 shutdown_ecore:
   ecore_shutdown();
 shutdown_evas:
   evas_shutdown();

   return --_ecore_evas_init_count;
}

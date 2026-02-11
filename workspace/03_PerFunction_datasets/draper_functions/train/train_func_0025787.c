_ecore_glib_shutdown(void)
{
#ifdef HAVE_GLIB
   if (!_ecore_glib_active) return;
   _ecore_glib_active = EINA_FALSE;

   if (ecore_main_loop_select_func_get() == _ecore_glib_select)
     ecore_main_loop_select_func_set(_ecore_glib_select_original);

   if (_ecore_glib_fds)
     {
        free(_ecore_glib_fds);
        _ecore_glib_fds = NULL;
     }
   _ecore_glib_fds_size = 0;

   if (_ecore_glib_cond)
     {
        g_cond_free(_ecore_glib_cond);
        _ecore_glib_cond = NULL;
     }
#endif
}

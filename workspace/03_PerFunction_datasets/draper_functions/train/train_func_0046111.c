e_remember_shutdown(void)
{
   E_FREE_LIST(hooks, e_border_hook_del);

   E_CONFIG_DD_FREE(e_remember_edd);
   E_CONFIG_DD_FREE(e_remember_list_edd);

   E_FREE_LIST(handlers, ecore_event_handler_del);
   if (remember_idler) ecore_idler_del(remember_idler);
   remember_idler = NULL;
   remember_idler_list = eina_list_free(remember_idler_list);

   return 1;
}

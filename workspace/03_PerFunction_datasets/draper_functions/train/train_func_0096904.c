e_modapi_shutdown(E_Module *m __UNUSED__)
{
   e_configure_registry_item_del("keyboard_and_mouse/xkbswitch");
   e_configure_registry_category_del("keyboard_and_mouse");

   if (_xkb.evh) ecore_event_handler_del(_xkb.evh);
   if (_xkb.cfd) e_object_del(E_OBJECT(_xkb.cfd));
   _xkb.cfd = NULL;
   _xkb.module = NULL;
   e_gadcon_provider_unregister(&_gc_class);

   return 1;
}

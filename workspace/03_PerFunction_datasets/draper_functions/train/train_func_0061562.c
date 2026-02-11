evry_view_help_init(void)
{
   if (!evry_api_version_check(EVRY_API_VERSION))
     return EINA_FALSE;

   view = E_NEW(Evry_View, 1);
   view->id = view;
   view->name = "Help";
   view->create = &_view_create;
   view->destroy = &_view_destroy;
   view->update = &_view_update;
   view->clear = &_view_clear;
   view->cb_key_down = &_cb_key_down;
   view->trigger = "?";

   evry_view_register(view, 2);

   return EINA_TRUE;
}

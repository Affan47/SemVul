evry_view_init(void)
{
   if (!evry_api_version_check(EVRY_API_VERSION))
     return EINA_FALSE;

   View *v = E_NEW(View, 1);

   v->view.id = EVRY_VIEW(v);
   v->view.name = "Icon View";
   v->view.create = &_view_create;
   v->view.destroy = &_view_destroy;
   v->view.update = &_view_update;
   v->view.clear = &_view_clear;
   v->view.cb_key_down = &_cb_key_down;
   v->mode = VIEW_MODE_NONE;

   evry_view_register(EVRY_VIEW(v), 1);

   view = v;

   return EINA_TRUE;
}

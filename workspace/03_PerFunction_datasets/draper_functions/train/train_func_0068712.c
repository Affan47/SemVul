_access_state_cb(void *data __UNUSED__,
                 Evas_Object *obj,
                 Elm_Widget_Item *item __UNUSED__)
{
   if (elm_widget_disabled_get(obj))
     return strdup(E_("State: Disabled"));

   return NULL;
}

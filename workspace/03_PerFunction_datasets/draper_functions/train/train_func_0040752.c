_access_state_cb(void *data,
                 Evas_Object *obj __UNUSED__,
                 Elm_Widget_Item *item __UNUSED__)
{
   Elm_List_Item *it = (Elm_List_Item *)data;
   if (!it) return NULL;

   if (it->base.disabled)
     return strdup(E_("State: Disabled"));

   return NULL;
}

_access_info_cb(void *data __UNUSED__, Evas_Object *obj __UNUSED__, Elm_Widget_Item *item)
{
   Elm_Toolbar_Item *it = (Elm_Toolbar_Item *)item;
   const char *txt = item->access_info;
   if (!txt) txt = it->label;
   if (txt) return strdup(txt);
   return NULL;
}

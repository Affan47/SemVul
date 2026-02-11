elm_widget_parent_set(Evas_Object *obj,
                      Evas_Object *parent)
{
   ELM_WIDGET_DATA_GET(obj, sd);

   if (!sd->api->parent_set) return;

   sd->api->parent_set(obj, parent);
}

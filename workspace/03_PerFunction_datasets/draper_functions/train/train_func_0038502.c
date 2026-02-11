_changed_size_hint_cb(void *data, Evas *evas __UNUSED__, Evas_Object *obj __UNUSED__, void *event __UNUSED__)
{
   Evas_Object *eo = (Evas_Object *)data;
   Widget_Data *wd = elm_widget_data_get(data);

   if (!wd) return;
   _sizing_eval(eo);
}

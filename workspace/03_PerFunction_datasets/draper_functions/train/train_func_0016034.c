_list_resize(void *data, Evas *e __UNUSED__, Evas_Object *obj,
                 void *event_info __UNUSED__)
{
   Widget_Data *wd = elm_widget_data_get(data);
   if (!wd) return;
   if (!wd->visible) return;
   if (wd->list_visible) return;

   wd->list_visible = EINA_TRUE;

   evas_object_show(wd->bg);
   evas_object_show(wd->base);
   evas_object_show(wd->arrow);
   _sizing_eval(obj);
}

_signal_callback_add_hook(Evas_Object *obj, const char *emission, const char *source, Edje_Signal_Cb func_cb, void *data)
{
   Widget_Data *wd = elm_widget_data_get(obj);
   if (!wd) return;
   edje_object_signal_callback_add(wd->ent, emission, source, func_cb, data);
   if (wd->scroller)
     edje_object_signal_callback_add(elm_smart_scroller_edje_object_get(wd->scroller),
                                     emission, source, func_cb, data);
}

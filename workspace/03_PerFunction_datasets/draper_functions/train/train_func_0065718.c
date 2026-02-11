_on_sub_object_size_hint_change(void *data,
                                Evas *e __UNUSED__,
                                Evas_Object *obj __UNUSED__,
                                void *event_info __UNUSED__)
{
   ELM_LAYOUT_DATA_GET(data, sd);
   if (ELM_WIDGET_DATA(sd)->frozen) return;
   ELM_LAYOUT_CLASS(ELM_WIDGET_DATA(sd)->api)->sizing_eval(data);
}

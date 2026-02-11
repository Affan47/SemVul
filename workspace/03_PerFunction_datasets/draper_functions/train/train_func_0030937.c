_signal_anchor_out(void *data, Evas_Object *obj __UNUSED__, const char *emission __UNUSED__, const char *source __UNUSED__)
{
   Widget_Data *wd = elm_widget_data_get(data);
   Elm_Entry_Anchor_Info ei;
   if (!wd) return;
   ei.name = emission + sizeof("nchor,mouse,out,");
   ei.button = 0;
   ei.x = ei.y = ei.w = ei.h = 0;

   _signal_anchor_geoms_do_things_with(wd, &ei);

   if (!wd->disabled)
     evas_object_smart_callback_call(data, SIG_ANCHOR_OUT, &ei);
}

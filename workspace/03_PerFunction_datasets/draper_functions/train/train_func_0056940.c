_ecore_evas_buffer_cb_focus_out(void *data, Evas *e __UNUSED__, Evas_Object *obj __UNUSED__, void *event_info __UNUSED__)
{
   Ecore_Evas *ee;

   ee = data;
   ee->prop.focused = 0;
   evas_focus_out(ee->evas);
   if (ee->func.fn_focus_out) ee->func.fn_focus_out(ee);
}

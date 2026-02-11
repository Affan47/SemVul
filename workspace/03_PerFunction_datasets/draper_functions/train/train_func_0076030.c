_elm_layout_smart_sizing_eval(Evas_Object *obj)
{
   ELM_LAYOUT_DATA_GET(obj, sd);

   if (sd->needs_size_calc) return;
   sd->needs_size_calc = EINA_TRUE;

   evas_object_smart_changed(obj);
}

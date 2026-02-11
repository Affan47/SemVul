_elm_layout_smart_on_focus(Evas_Object *obj)
{
   ELM_LAYOUT_DATA_GET(obj, sd);

   if (elm_widget_focus_get(obj))
     {
        elm_layout_signal_emit(obj, "elm,action,focus", "elm");
        evas_object_focus_set(ELM_WIDGET_DATA(sd)->resize_obj, EINA_TRUE);
     }
   else
     {
        elm_layout_signal_emit(obj, "elm,action,unfocus", "elm");
        evas_object_focus_set(ELM_WIDGET_DATA(sd)->resize_obj, EINA_FALSE);
     }

   return EINA_TRUE;
}

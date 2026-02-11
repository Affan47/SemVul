elm_widget_content_part_set(Evas_Object *obj, const char *part, Evas_Object *content)
{
   API_ENTRY return;

   if (!sd->api) return;
   if (_elm_legacy_is(obj) && COMPAT_SMART_DATA(sd)->content_set)
     COMPAT_SMART_DATA(sd)->content_set(obj, part, content);
   else if (evas_object_smart_type_check(obj, "elm_container"))
     ELM_CONTAINER_CLASS(sd->api)->content_set(obj, part, content);
}

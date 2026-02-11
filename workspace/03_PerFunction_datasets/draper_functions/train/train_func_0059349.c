elm_widget_type_set(Evas_Object *obj,
                    const char  *type)
{
   API_ENTRY return;

   if (!_elm_legacy_is(obj)) return;

   eina_stringshare_replace(&(COMPAT_SMART_DATA(sd)->type), type);
}

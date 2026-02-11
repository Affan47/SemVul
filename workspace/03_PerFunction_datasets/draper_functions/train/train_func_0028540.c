_item_icon_set(Evas_Object *icon_obj, const char *type, const char *icon)
{
   char icon_str[512];

   if ((!type) || (!*type)) goto end;
   if ((!icon) || (!*icon)) return EINA_FALSE;
   if ((snprintf(icon_str, sizeof(icon_str), "%s%s", type, icon) > 0)
       && (elm_icon_standard_set(icon_obj, icon_str)))
     return EINA_TRUE;
end:
   if (elm_icon_standard_set(icon_obj, icon))
     return EINA_TRUE;
   WRN("couldn't find icon definition for '%s'", icon);
   return EINA_FALSE;
}

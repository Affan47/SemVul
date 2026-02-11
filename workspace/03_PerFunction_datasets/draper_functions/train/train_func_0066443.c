_e_xsettings_string_set(const char *name, const char *value)
{
   Setting *s;
   Eina_List *l;

   if (!name) return;
   if (name == _setting_theme_name)
     e_config->xsettings.net_theme_name_detected = value;
   name = eina_stringshare_add(name);

   EINA_LIST_FOREACH(settings, l, s)
     {
        if (s->type != SETTING_TYPE_STRING) continue;
        if (s->name == name) break;
     }
   if (!value)
     {
        if (!s) return;
        DBG("remove %s\n", name);
        eina_stringshare_del(name);
        eina_stringshare_del(s->name);
        eina_stringshare_del(s->s.value);
        settings = eina_list_remove(settings, s);
        E_FREE(s);
        return;
     }
   if (s)
     {
        DBG("update %s %s\n", name, value);
        eina_stringshare_del(name);
        eina_stringshare_replace(&s->s.value, value);
     }
   else
     {
        DBG("add %s %s\n", name, value);
        s = E_NEW(Setting, 1);
        s->type = SETTING_TYPE_STRING;
        s->name = name;
        s->s.value = eina_stringshare_add(value);
        settings = eina_list_append(settings, s);
     }


   s->length = 12;
   s->length += OFFSET_ADD(strlen(name));
   s->length += OFFSET_ADD(strlen(value));
   s->last_change = ecore_x_current_time_get();
}

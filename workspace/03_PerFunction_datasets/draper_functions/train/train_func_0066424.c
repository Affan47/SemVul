e_theme_config_get(const char *category)
{
   E_Config_Theme *ect = NULL;
   Eina_List *next;


   EINA_LIST_FOREACH(e_config->themes, next, ect)
     {
        if (!strcmp(ect->category, category))
          return ect;
     }
   return NULL;
}

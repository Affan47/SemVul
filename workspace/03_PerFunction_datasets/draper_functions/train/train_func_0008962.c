gc_locale_gets_list_name(){

  static GList *gcompris_locales_list_name = NULL;
  GList *list;

  if(gcompris_locales_list_name) {
    g_list_free(gcompris_locales_list_name);
    gcompris_locales_list_name = NULL;
  }

  for (list = gc_locale_gets_list(); list != NULL; list = list->next)
    {
      gcompris_locales_list_name =			\
	g_list_insert_sorted(gcompris_locales_list_name,
			     g_strdup( gc_locale_get_name( list->data) ),
			     (GCompareFunc) g_strcmp0  );
    }
  return gcompris_locales_list_name;
}

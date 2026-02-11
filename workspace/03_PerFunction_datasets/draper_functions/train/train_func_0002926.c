fpm_create_category_list(gint edit_flag)
{
  GList *list;
  fpm_data *data;


  list = g_list_first(glb_cat_string_list);
  while(list!=NULL)
  {
    g_assert(list->data!=NULL);
    g_free(list->data);
    list=g_list_next(list);
  }
  g_list_free(glb_cat_string_list);
  glb_cat_string_list = NULL;


  list = g_list_first(glb_pass_list);
  while(list!=NULL)
  {
    data = list->data;
    if (
	strcmp(data->category, "") &&
	    g_list_find_custom(glb_cat_string_list, data->category, (GCompareFunc) g_utf8_collate) == NULL)
    {
      g_assert(data->category != NULL);
      glb_cat_string_list = g_list_insert_sorted(glb_cat_string_list,
		g_strdup(data->category), (GCompareFunc) g_utf8_collate);
    }
    list=g_list_next(list);
  }


  if(edit_flag)
  {

    glb_cat_string_list = g_list_prepend(glb_cat_string_list, g_strdup(""));
  }
  else
  {

    glb_cat_string_list = g_list_prepend(glb_cat_string_list, g_strdup(FPM_NONE_CAT_MSG));
    glb_cat_string_list = g_list_prepend(glb_cat_string_list, g_strdup(FPM_DEFAULT_CAT_MSG));
    glb_cat_string_list = g_list_prepend(glb_cat_string_list, g_strdup(FPM_ALL_CAT_MSG));
  }
}

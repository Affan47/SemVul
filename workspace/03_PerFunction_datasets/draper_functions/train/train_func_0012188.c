fpm_create_launcher_string_list()
{
  GList * list;
  fpm_launcher* launcher;

  glb_launcher_string_list=NULL;
  list=g_list_first(glb_launcher_list);
  glb_launcher_string_list = g_list_append(glb_launcher_string_list, g_strdup(C_("key_file","<NONE>")));
  while (list!= NULL)
  {
    launcher=list->data;
    glb_launcher_string_list=g_list_append(glb_launcher_string_list, g_strdup(launcher->title));
    list=g_list_next(list);
  }
}

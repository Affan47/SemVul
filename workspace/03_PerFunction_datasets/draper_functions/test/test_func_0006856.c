s_attrib_name_in_list(STRING_LIST *name_value_list, char *name)
{
  STRING_LIST *local_list_item;
  char *local_name;

  for (local_list_item = name_value_list;
       local_list_item != NULL;
       local_list_item = local_list_item->next) {

    if (local_list_item->data == NULL)
      continue;

    local_name = u_basic_breakup_string(local_list_item->data, '=', 0);
    if (strcmp(local_name, name) == 0) {
      g_free (local_name);
      return TRUE;
    }
    g_free (local_name);
  }
  return FALSE;
}

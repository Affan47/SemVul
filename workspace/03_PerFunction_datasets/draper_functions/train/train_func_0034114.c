s_check_graphical (const GList *obj_list, SYMCHECK *s_current)
{
  char *temp;


  temp = o_attrib_search_floating_attribs_by_name (obj_list, "graphical", 0);

  if (temp) {
    s_current->graphical_symbol=TRUE;
    g_free(temp);
  }
}

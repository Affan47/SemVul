remove_class_name (gchar       **class_list,
                   const gchar  *class_name)
{
  const gchar *match, *end;
  gchar *new_class_list;

  if (!*class_list)
    return FALSE;

  if (strcmp (*class_list, class_name) == 0)
    {
      g_free (*class_list);
      *class_list = NULL;
      return TRUE;
    }

  match = find_class_name (*class_list, class_name);
  if (!match)
    return FALSE;
  end = match + strlen (class_name);


  if (match != *class_list)
    match--;
  else
    end++;

  new_class_list = g_strdup_printf ("%.*s%s", (int)(match - *class_list),
                                    *class_list, end);
  g_free (*class_list);
  *class_list = new_class_list;

  return TRUE;
}

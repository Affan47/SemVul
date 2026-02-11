list_superclasses (GType type)
{
  GString *str = g_string_new ("");
  gboolean last=TRUE;

  while (type != 0)
    {
      if (!last)
        g_string_prepend (str, "/");
      g_string_prepend (str, "</a>");
      g_string_prepend (str, g_type_name (type));
      g_string_prepend (str, "'>");
      g_string_prepend (str, g_type_name (type));
      g_string_prepend (str, "<a href='#");
      type = g_type_parent (type);
      last = FALSE;
    }
  fprintf (file, "%s\n", str->str);
  g_string_free (str, TRUE);
}

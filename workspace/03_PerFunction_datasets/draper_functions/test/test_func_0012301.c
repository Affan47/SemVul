show_themed_icon_names (GThemedIcon *icon, gboolean symbolic, int indent)
{
  char **names;
  char **iter;

  g_print ("%*s%sthemed icons:", indent, " ", symbolic ? "symbolic " : "");

  names = NULL;

  g_object_get (icon, "names", &names, NULL);

  for (iter = names; *iter; iter++)
    g_print ("  [%s]", *iter);

  g_print ("\n");
  g_strfreev (names);
}

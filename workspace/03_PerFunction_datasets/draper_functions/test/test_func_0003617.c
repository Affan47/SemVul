parse_args (gint argc, gchar **argv, gchar **name, gchar **domain, gchar **icon_url, gchar **mime_types, gchar **desktop_name)
{
  if (argc != 5 && argc != 6)
    return FALSE;

  *name = argv[1];
  *domain = argv[2];
  *icon_url = argv[3];
  *mime_types = argv[4];
  if (argc == 6)
    {
      *desktop_name = argv[5];
    }
  else
    {
      *desktop_name = NULL;
    }

  if (g_strcmp0 (*icon_url, "none") == 0)
    {
      *icon_url = NULL;
    }
  if (g_strcmp0 (*mime_types, "none") == 0)
    {
      *mime_types = NULL;
    }

  return TRUE;
}

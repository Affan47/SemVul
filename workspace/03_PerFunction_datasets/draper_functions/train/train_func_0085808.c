terminal_util_load_builder_file (const char *filename,
                                 const char *object_name,
                                 ...)
{
  char *path;
  GtkBuilder *builder;
  GError *error = NULL;
  va_list args;

  path = g_build_filename (TERM_PKGDATADIR, filename, NULL);
  builder = gtk_builder_new ();
  if (!gtk_builder_add_from_file (builder, path, &error)) {
    g_warning ("Failed to load %s: %s\n", filename, error->message);
    g_error_free (error);
    g_free (path);
    g_object_unref (builder);
    return FALSE;
  }
  g_free (path);

  va_start (args, object_name);

  while (object_name) {
    GObject **objectptr;

    objectptr = va_arg (args, GObject**);
    *objectptr = gtk_builder_get_object (builder, object_name);
    if (!*objectptr) {
      g_warning ("Failed to fetch object \"%s\"\n", object_name);
      break;
    }

    object_name = va_arg (args, const char*);
  }

  va_end (args);

  g_object_unref (builder);
  return object_name == NULL;
}

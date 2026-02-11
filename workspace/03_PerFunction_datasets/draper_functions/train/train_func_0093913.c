load_modules_from_string (SwCore *core, const char *s)
{
  char **modules, **basename;

  modules = g_strsplit (s, ",", 0);

  for (basename = modules; *basename; basename++) {
    char *name, *path;

    name = g_strconcat ("lib", *basename, NULL);
    path = g_build_filename (SOCIALWEB_SERVICES_MODULES_DIR, name, NULL);

    load_module (core, path);

    g_free (path);
    g_free (name);
  }

  g_strfreev (modules);
}

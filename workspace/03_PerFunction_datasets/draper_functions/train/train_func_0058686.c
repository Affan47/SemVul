gettext_initialization (void)
{
#ifdef ENABLE_NLS
  static gboolean gettext_initialized = FALSE;

  if (!gettext_initialized)
    {
      const char *dir = g_getenv ("ATK_ALT_LOCALEDIR");

      gettext_initialized = TRUE;
      if (dir == NULL)
        dir = ATK_LOCALEDIR;

      bindtextdomain (GETTEXT_PACKAGE, dir);
#ifdef HAVE_BIND_TEXTDOMAIN_CODESET
      bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
#endif
    }
#endif
}

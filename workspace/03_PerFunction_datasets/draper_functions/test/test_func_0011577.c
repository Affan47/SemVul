xdg_create_link         (gchar  *src,
                         gchar  *dest,
                         gchar  *icon)
{
  gchar *link_extension = "desktop";
  gchar *link_filename = g_strdup_printf ("%s.%s", dest, link_extension);

  if (!g_file_test (link_filename, G_FILE_TEST_EXISTS))
    {
       gchar *exec = g_strdup_printf ("xdg-open %s\n", src);
       xdg_create_desktop_entry (link_filename, "Application", PACKAGE_NAME, icon, exec);
       g_free (exec);
    }

  g_free (link_filename);
}

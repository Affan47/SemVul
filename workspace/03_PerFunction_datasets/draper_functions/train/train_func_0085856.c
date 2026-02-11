testing_init (gint    *argc,
              gchar ***argv)
{
  GError *error = NULL;
  static gboolean initialized = FALSE;

  if (initialized)
    return;

  gtk_test_init (argc, argv, NULL);


  testing_util_init ();

  g_irepository_prepend_search_path (BUILDDIR "/libpeas-gtk");

  g_irepository_require (g_irepository_get_default (), "PeasGtk", "1.0", 0, &error);
  g_assert_no_error (error);

  initialized = TRUE;
}

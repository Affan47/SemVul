script_animation (TestConformSimpleFixture *fixture,
                  gconstpointer dummy)
{
  ClutterScript *script = clutter_script_new ();
  GObject *animation = NULL;
  GError *error = NULL;
  gchar *test_file;

  test_file = clutter_test_get_data_file ("test-script-animation.json");
  clutter_script_load_from_file (script, test_file, &error);
  if (g_test_verbose () && error)
    g_print ("Error: %s", error->message);

#if GLIB_CHECK_VERSION (2, 20, 0)
  g_assert_no_error (error);
#else
  g_assert (error == NULL);
#endif

  animation = clutter_script_get_object (script, "test");
  g_assert (CLUTTER_IS_ANIMATION (animation));

  g_object_unref (script);
  g_free (test_file);
}

units_cache (TestConformSimpleFixture *fixture,
             gconstpointer data)
{
  ClutterUnits units;
  ClutterSettings *settings;
  gfloat pixels;
  gint old_dpi;

  settings = clutter_settings_get_default ();
  g_object_get (settings, "font-dpi", &old_dpi, NULL);

  g_object_set (settings, "font-dpi", 96 * 1024, NULL);
  clutter_units_from_em (&units, 1.0);
  pixels = clutter_units_to_pixels (&units);

  g_object_set (settings, "font-dpi", ((96 * 2) * 1024), NULL);
  g_assert_cmpfloat (clutter_units_to_pixels (&units), !=, pixels);

  g_object_set (settings, "font-dpi", (96 * 1024), NULL);
  g_assert_cmpfloat (clutter_units_to_pixels (&units), ==, pixels);

  g_object_set (settings, "font-dpi", old_dpi, NULL);
}

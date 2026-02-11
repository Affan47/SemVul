setup_fixture_simple (ManifestTestFixture *fixture, gconstpointer user_data)
{
  gboolean loaded;
  fixture->manifest = unity_webapps_application_manifest_new ();
  loaded = unity_webapps_application_manifest_load_from_file (fixture->manifest,
                                                              TESTDATADIR "test-manifest-1.json");
  g_assert (loaded);
}

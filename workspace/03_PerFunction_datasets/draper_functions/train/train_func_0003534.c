main (int argc, char *argv[])
{
    gsize n_tests;

#if !(GLIB_CHECK_VERSION (2, 36, 0))
    g_type_init ();
#endif

    g_test_init (&argc, &argv, NULL);
    g_test_bug_base ("http://ufo.kit.edu/ufo/ticket");

    struct {
        const gchar *name;
        void (*test_func) (Fixture *fixture, gconstpointer data);
    }
    tests[] = {
        {"/factory", test_factory},
        {"/factory/hashtable", test_factory_hashtable},
        {"/signal", test_signal},
        {"/recording", test_recording},
        {"/recording/signal", test_recording_signal},
        {"/recording/asynchronous", test_recording_async},
        {"/recording/buffered", test_recording_buffered},
        {"/properties/base", test_base_properties},
        {"/properties/recording", test_recording_property},
        {"/properties/binnings", test_binnings_properties},
        {"/properties/frames-per-second", test_fps_property},
        {"/properties/units", test_property_units},
        {"/properties/units/overwrite", test_overwriting_units},
        {"/properties/can-be-written", test_can_be_written},
    };

    n_tests = sizeof(tests) / sizeof(tests[0]);

    for (gsize i = 0; i < n_tests; i++)
        g_test_add (tests[i].name, Fixture, NULL, fixture_setup, tests[i].test_func, fixture_teardown);

    return g_test_run ();
}

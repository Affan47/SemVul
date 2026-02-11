test_factory_hashtable (Fixture *fixture, gconstpointer data)
{
    GError *error = NULL;

    guint checkvalue = 42;

    gchar *foo = "roi-x0";
    gchar *bar = "roi-y0";
    GValue baz = G_VALUE_INIT;
    g_value_init(&baz, G_TYPE_UINT);
    g_value_set_uint(&baz, checkvalue);

    GHashTable *ght = g_hash_table_new (NULL, NULL);
    g_hash_table_insert(ght, foo, &baz);
    g_hash_table_insert(ght, bar, &baz);

    UcaCamera *camera = uca_plugin_manager_get_camerah (fixture->manager,
                                                     "mock", ght, &error);
    g_hash_table_destroy(ght);

    g_assert (error == NULL);
    g_assert (camera);

    guint roi_x0 = 0;
    g_object_get (G_OBJECT (camera), "roi-x0", &roi_x0, NULL);
    g_assert (roi_x0 == checkvalue);

    guint roi_y0 = 0;
    g_object_get (G_OBJECT (camera), "roi-y0", &roi_y0, NULL);
    g_assert (roi_y0 == checkvalue);

    g_object_unref(camera);
}

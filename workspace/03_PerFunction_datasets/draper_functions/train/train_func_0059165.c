gwy_stock_register_stock_items(void)
{
    gchar *pixmap_paths[3];

    g_return_if_fail(!the_icon_factory);
    gtk_icon_size_register(GWY_ICON_SIZE_ABOUT, 60, 60);
    pixmap_paths[0] = gwy_find_self_dir("pixmaps");
    pixmap_paths[1] = g_build_filename(gwy_get_user_dir(), "pixmaps", NULL);
    if (!g_file_test(pixmap_paths[1], G_FILE_TEST_IS_DIR)) {
        g_free(pixmap_paths[1]);
        pixmap_paths[1] = NULL;
    }
    pixmap_paths[2] = NULL;

    the_icon_factory = gtk_icon_factory_new();
    register_icons((const gchar**)pixmap_paths, the_icon_factory);

    g_free(pixmap_paths[0]);
    g_free(pixmap_paths[1]);
    gtk_icon_factory_add_default(the_icon_factory);
}

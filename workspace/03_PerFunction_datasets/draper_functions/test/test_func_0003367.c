initialize() {
    g_texture_width = 2048;
    g_texture_height = 2048;
    int max_texture_size = fs_ml_get_max_texture_size();
    if (max_texture_size > 0) {
        if (max_texture_size < g_texture_width) {
            g_texture_width = max_texture_size;
        }
        if (max_texture_size < g_texture_height) {
            g_texture_height = max_texture_size;
        }
    }
    fs_log("using text cache texture size %dx%d\n", g_texture_width,
            g_texture_height);

    initialize_cache();
    create_text_texture();
    fs_gl_add_context_notification(context_notification_handler, NULL);
    g_buffer = malloc(g_texture_width * 32 * 4);

#ifdef USE_FREETYPE
    init_freetype();
#endif
    g_initialized = 1;
}

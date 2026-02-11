main (int argc, char *argv[])
{
    GOptionContext *context;
    UcaPluginManager *manager;
    UcaCamera *camera;
    GError *error = NULL;

    static Options opts = {
        .n_frames = -1,
        .duration = -1.0,
        .filename = NULL,
#ifdef HAVE_LIBTIFF
        .write_tiff = FALSE,
#endif
    };

    static GOptionEntry entries[] = {
        { "num-frames", 'n', 0, G_OPTION_ARG_INT, &opts.n_frames, "Number of frames to acquire", "N" },
        { "duration", 'd', 0, G_OPTION_ARG_DOUBLE, &opts.duration, "Duration in seconds", NULL },
        { "output", 'o', 0, G_OPTION_ARG_STRING, &opts.filename, "Output file name", "FILE" },
#ifdef HAVE_LIBTIFF
        { "write-tiff", 't', 0, G_OPTION_ARG_NONE, &opts.write_tiff, "Write as TIFF", NULL },
#endif
        { NULL }
    };

#if !(GLIB_CHECK_VERSION (2, 36, 0))
    g_type_init();
#endif

    manager = uca_plugin_manager_new ();
    context = uca_option_context_new (manager);
    g_option_context_add_main_entries (context, entries, NULL);

    if (!g_option_context_parse (context, &argc, &argv, &error)) {
        g_print ("Failed parsing arguments: %s\n", error->message);
        goto cleanup_manager;
    }

    if (argc < 2) {
        g_print ("%s\n", g_option_context_get_help (context, TRUE, NULL));
        goto cleanup_manager;
    }

    if (opts.n_frames < 0 && opts.duration < 0.0) {
        g_print ("You must specify at least one of --num-frames and --output.\n");
        goto cleanup_manager;
    }

    camera = uca_plugin_manager_get_camera (manager, argv[1], &error, NULL);

    if (camera == NULL) {
        g_print ("Error during initialization: %s\n", error->message);
        goto cleanup_camera;
    }

    error = record_frames (camera, &opts);

    if (error != NULL)
        g_print ("Error: %s\n", error->message);

    g_option_context_free (context);

cleanup_camera:
    g_object_unref (camera);

cleanup_manager:
    g_object_unref (manager);

    return error != NULL ? 1 : 0;
}

set_initial_geometry(void)
{
    GdkGeometry size_hints = {
        1, 1, 0, 0, 1, 1, 1, 1, 0.0, 0.0, GDK_GRAVITY_NORTH_WEST
    };

    if (!options->initial_geometry)
        goto fail;

    if (options->fullscreen) {
        g_printerr(_("Ignoring initial geometry (%s) as"
                     " fullscreen mode is requested\n"),
                   options->initial_geometry);
        goto fail;
    }

    gtk_window_set_geometry_hints(main_window, GTK_WIDGET(main_window),
                                  &size_hints,
                                  GDK_HINT_MIN_SIZE | GDK_HINT_BASE_SIZE |
                                  GDK_HINT_RESIZE_INC);

    if (!gtk_window_parse_geometry(main_window, options->initial_geometry)) {
        g_printerr(_("Cannot parse geometry: %s\n"), options->initial_geometry);
        goto fail;
    }

    return;

  fail:
    g_free(options->initial_geometry);
    options->initial_geometry = NULL;
}

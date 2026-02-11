set_style_fg_bg (GObject* obj, GtkSourceStyleScheme* scheme,
                      gchar* styleName, gchar* defaultBG) {
    GtkSourceStyle *style = NULL;

    gchar *bg = NULL;
    gchar *fg = NULL;
    gboolean foreground_set;
    gboolean background_set;
    GdkColor foreground;
    GdkColor background;


    if (scheme == NULL) {
        goto set_style_fg_bg_return_defaults;
    }

    style = gtk_source_style_scheme_get_style (scheme, styleName);

    if (style == NULL) {
        goto set_style_fg_bg_return_defaults;
    }


    g_object_get (style,
                  "foreground-set", &foreground_set,
                  "foreground", &fg,
                  "background-set", &background_set,
                  "background", &bg,
                  NULL);

    if (foreground_set) {
        if (fg == NULL || !gdk_color_parse (fg, &foreground))
            foreground_set = FALSE;
    }

    if (background_set) {
        if (bg == NULL || !gdk_color_parse (bg, &background))
            background_set = FALSE;
    }

    g_free(fg);
    g_free(bg);

    if (background_set && foreground_set) {


    } else if (!background_set && foreground_set) {

        gdk_color_parse(defaultBG, &background);
        gdouble diff = ABS(gdkcolor_luminance(foreground) -
                gdkcolor_luminance(background));
        if (diff < 0.5) {
            slog(L_INFO, "Style \"%s\" defines a foreground, but no background "
                         "color. As the fourground color has not enough "
                         "contrast to Gummis default background color, the "
                         "foreground color has been adjusted.\n", styleName);
            if (gdkcolor_luminance(background) > 0.5) {
                gdk_color_parse("black", &foreground);
            } else {
                gdk_color_parse("white", &foreground);
            }
        }
    } else if (background_set && !foreground_set) {

        if (gdkcolor_luminance(background) > 0.5) {
            gdk_color_parse("black", &foreground);
        } else {
            gdk_color_parse("white", &foreground);
        }
    } else {

        goto set_style_fg_bg_return_defaults;
    }

    g_object_set (obj, "foreground-gdk", &foreground,
                        "background-gdk", &background, NULL);
    return;

set_style_fg_bg_return_defaults:


    gdk_color_parse(defaultBG, &background);
    if (gdkcolor_luminance(background) > 0.5) {
        gdk_color_parse("black", &foreground);
    } else {
        gdk_color_parse("white", &foreground);
    }

    g_object_set (obj, "foreground-gdk", &foreground,
                        "background-gdk", &background, NULL);

}

conversion_display_hide_log_window(Conversion *conv) {


    if (prefs_get_int(FILE_CONVERT_DISPLAY_LOG)) {
        if (conv->log_window_hidden && !conv->log_window_shown) {
            gtk_widget_show(conv->log_window);
            if (conv->log_window_posx != G_MININT) {
                gtk_window_move(GTK_WINDOW (conv->log_window), conv->log_window_posx, conv->log_window_posy);
            }
        }
        conv->log_window_shown = TRUE;
    }
    else {
        if (conv->log_window_shown) {
            gint posx, posy;
            gtk_window_get_position(GTK_WINDOW (conv->log_window), &posx, &posy);
            conv->log_window_posx = posx;
            conv->log_window_posy = posy;
        }
        conv->log_window_shown = FALSE;
        conv->log_window_hidden = TRUE;
        gtk_widget_hide(conv->log_window);
    }
}

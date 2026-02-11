set_slider_range(gint index) {
    g_signal_handler_block(G_OBJECT(cdwidget->cdslider), slide_signal_id);

    gint slider_ubound = g_list_length(album_key_list) - IMG_TOTAL;
    if (slider_ubound < 1) {


        slider_ubound = 1;
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->cdslider), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->leftbutton), FALSE);
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->rightbutton), FALSE);
    }
    else {
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->cdslider), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->leftbutton), TRUE);
        gtk_widget_set_sensitive(GTK_WIDGET(cdwidget->rightbutton), TRUE);
    }

    gtk_range_set_range(GTK_RANGE (cdwidget->cdslider), 0, slider_ubound);
    if (index >= 0 && index <= slider_ubound)
        gtk_range_set_value(GTK_RANGE (cdwidget->cdslider), index);
    else
        gtk_range_set_value(GTK_RANGE (cdwidget->cdslider), 0);

    g_signal_handler_unblock(G_OBJECT(cdwidget->cdslider), slide_signal_id);
}

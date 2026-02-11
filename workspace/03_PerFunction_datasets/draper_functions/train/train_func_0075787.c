gwy_mask_color_selector_run(const gchar *dialog_title,
                            GtkWindow *parent,
                            GwyColorButton *color_button,
                            GwyContainer *container,
                            const gchar *prefix)
{
    GtkWidget *selector, *dialog;
    MaskColorSelectorData *mcsdata;
    GdkColor gdkcolor;
    guint16 gdkalpha;
    GwyRGBA rgba;
    gint response;
    gboolean parent_is_modal;

    g_return_if_fail(prefix && *prefix == '/');

    mcsdata = g_new(MaskColorSelectorData, 1);
    mcsdata->color_button = color_button;
    mcsdata->container = container;
    mcsdata->prefix = g_strdup(prefix);

    gwy_rgba_get_from_container(&rgba, container, mcsdata->prefix);
    gwy_rgba_to_gdk_color(&rgba, &gdkcolor);
    gdkalpha = gwy_rgba_to_gdk_alpha(&rgba);

    dialog = gtk_color_selection_dialog_new(dialog_title
                                            ? dialog_title
                                            : _("Change Mask Color"));
    selector = GTK_COLOR_SELECTION_DIALOG(dialog)->colorsel;
    gtk_color_selection_set_current_color(GTK_COLOR_SELECTION(selector),
                                          &gdkcolor);
    gtk_color_selection_set_current_alpha(GTK_COLOR_SELECTION(selector),
                                          gdkalpha);
    gtk_color_selection_set_has_palette(GTK_COLOR_SELECTION(selector), FALSE);
    gtk_color_selection_set_has_opacity_control(GTK_COLOR_SELECTION(selector),
                                                TRUE);
    g_signal_connect(selector, "color-changed",
                     G_CALLBACK(mask_color_updated_cb), mcsdata);

    if (parent) {
        gtk_window_set_transient_for(GTK_WINDOW(dialog), parent);


        parent_is_modal = gtk_window_get_modal(parent);
        if (parent_is_modal)
            gtk_window_set_modal(parent, FALSE);
    }
    else
        parent_is_modal = FALSE;

    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    if (parent_is_modal)
        gtk_window_set_modal(parent, TRUE);

    if (response != GTK_RESPONSE_OK) {
        gwy_rgba_store_to_container(&rgba, container, mcsdata->prefix);
        if (mcsdata->color_button)
            gwy_color_button_set_color(mcsdata->color_button, &rgba);
    }
    g_free(mcsdata->prefix);
    g_free(mcsdata);
}

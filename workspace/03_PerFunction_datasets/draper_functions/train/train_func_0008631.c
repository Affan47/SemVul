font_view_application_do_overview (FontViewApplication *self)
{
    g_clear_object (&self->font_file);

    if (self->back_button) {
        gtk_widget_destroy (self->back_button);
        self->back_button = NULL;
    }

    if (self->info_button) {
        gtk_widget_destroy (self->info_button);
        self->info_button = NULL;
    }

    if (self->install_button) {
        gtk_widget_destroy (self->install_button);
        self->install_button = NULL;
    }

    font_view_ensure_model (self);

    gd_header_bar_set_title (GD_HEADER_BAR (self->header), _("All Fonts"));
    gd_header_bar_set_subtitle (GD_HEADER_BAR (self->header), NULL);

    if (self->icon_view == NULL) {
        GtkWidget *icon_view;
        GtkCellRenderer *cell;

        self->icon_view = icon_view = gtk_icon_view_new_with_model (self->model);
        g_object_set (icon_view,
                      "column-spacing", VIEW_COLUMN_SPACING,
                      "margin", VIEW_MARGIN,
                      NULL);

        gtk_widget_set_vexpand (GTK_WIDGET (icon_view), TRUE);
        gtk_icon_view_set_selection_mode (GTK_ICON_VIEW (icon_view), GTK_SELECTION_NONE);
        gtk_container_add (GTK_CONTAINER (self->swin_view), icon_view);

        cell = gtk_cell_renderer_pixbuf_new ();
        g_object_set (cell,
                      "xalign", 0.5,
                      "yalign", 0.5,
                      NULL);

        gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (icon_view), cell, FALSE);
        gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (icon_view), cell,
                                       "pixbuf", COLUMN_ICON);

        cell = gtk_cell_renderer_text_new ();
        g_object_set (cell,
                      "alignment", PANGO_ALIGN_CENTER,
                      "xalign", 0.5,
                      "wrap-mode", PANGO_WRAP_WORD_CHAR,
                      "wrap-width", VIEW_ITEM_WRAP_WIDTH,
                      NULL);
        gtk_cell_layout_pack_start (GTK_CELL_LAYOUT (icon_view), cell, FALSE);
        gtk_cell_layout_add_attribute (GTK_CELL_LAYOUT (icon_view), cell,
                                       "text", COLUMN_NAME);

        g_signal_connect (icon_view, "button-release-event",
                          G_CALLBACK (icon_view_release_cb), self);
    }

    gtk_widget_show_all (self->main_window);
    gd_stack_set_visible_child_name (GD_STACK (self->stack), "overview");
}

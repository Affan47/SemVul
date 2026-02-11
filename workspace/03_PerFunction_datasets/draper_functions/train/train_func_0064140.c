gwy_tool_like_button_new(const gchar *label_text,
                         const gchar *stock_id)
{
    GtkWidget *button, *image, *vbox, *label;
    GdkPixbuf *pixbuf;

    button = gtk_button_new();
    vbox = gtk_vbox_new(FALSE, 2);
    gtk_container_add(GTK_CONTAINER(button), vbox);

    if (stock_id) {
        pixbuf = gtk_widget_render_icon(button, stock_id,
                                        GTK_ICON_SIZE_LARGE_TOOLBAR,
                                        "toolitem");
    }
    else {

        pixbuf = gtk_widget_render_icon(button, GTK_STOCK_OK,
                                        GTK_ICON_SIZE_LARGE_TOOLBAR,
                                        "toolitem");
        gdk_pixbuf_fill(pixbuf, 0);
    }
    image = gtk_image_new_from_pixbuf(pixbuf);
    g_object_unref(pixbuf);
    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);

    label = gtk_label_new_with_mnemonic(label_text);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_label_set_mnemonic_widget(GTK_LABEL(label), button);

    return button;
}

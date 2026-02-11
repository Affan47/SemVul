infoscreengui_init (GtkBuilder* builder) {
    g_return_val_if_fail (GTK_IS_BUILDER (builder), NULL);

    GuInfoscreenGui* is = g_new0 (GuInfoscreenGui, 1);

    is->viewport =
        GTK_VIEWPORT (gtk_builder_get_object (builder, "preview_vport"));
    is->errorpanel =
        GTK_WIDGET(gtk_builder_get_object (builder, "errorpanel"));
    is->drawarea =
        GTK_WIDGET (gtk_builder_get_object (builder, "preview_draw"));

    is->header =
        GTK_LABEL (gtk_builder_get_object (builder, "error_header"));
    is->image =
        GTK_IMAGE (gtk_builder_get_object (builder, "error_image"));
    is->details =
        GTK_LABEL (gtk_builder_get_object (builder, "error_details"));
    return is;
}

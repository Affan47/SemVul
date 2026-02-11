template_init (GtkBuilder* builder) {
    g_return_val_if_fail (GTK_IS_BUILDER (builder), NULL);
    GuTemplate* t = g_new0 (GuTemplate, 1);
    t->templatewindow =
        GTK_WINDOW (gtk_builder_get_object (builder, "templatewindow"));
    t->templateview =
        GTK_TREE_VIEW (gtk_builder_get_object (builder, "template_treeview"));
    t->list_templates =
        GTK_LIST_STORE (gtk_builder_get_object (builder, "list_templates"));
    t->template_label =
        GTK_LABEL (gtk_builder_get_object (builder, "template_label"));
    t->template_add =
        GTK_WIDGET (gtk_builder_get_object (builder, "template_add"));
    t->template_remove =
        GTK_WIDGET (gtk_builder_get_object (builder, "template_remove"));
    t->template_open =
        GTK_WIDGET (gtk_builder_get_object (builder, "template_open"));
    t->template_render = GTK_CELL_RENDERER_TEXT (
            gtk_builder_get_object (builder, "template_renderer"));
    t->template_col = GTK_TREE_VIEW_COLUMN (
            gtk_builder_get_object (builder, "template_column"));
    gtk_tree_view_column_set_sort_column_id (t->template_col, 0);
    return t;
}

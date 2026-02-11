render_objects(G_GNUC_UNUSED GtkTreeViewColumn *column,
               GtkCellRenderer *renderer,
               GtkTreeModel *model,
               GtkTreeIter *iter,
               G_GNUC_UNUSED gpointer user_data)
{
    gchar buffer[16];
    GwySelection *sel;

    gtk_tree_model_get(model, iter, MODEL_OBJECT, &sel, -1);
    g_return_if_fail(GWY_IS_SELECTION(sel));
    g_snprintf(buffer, sizeof(buffer), "%d", gwy_selection_get_data(sel, NULL));
    g_object_set(renderer, "text", buffer, NULL);
    g_object_unref(sel);
}

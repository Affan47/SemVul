render_symmetry(G_GNUC_UNUSED GtkTreeViewColumn *column,
                GtkCellRenderer *renderer,
                GtkTreeModel *model,
                GtkTreeIter *iter,
                gpointer data)
{
    GwyConvolutionFilterPreset *preset;
    ConvolutionFilterSymmetryType sym;
    const gchar *str;

    gtk_tree_model_get(model, iter, 0, &preset, -1);
    if (GPOINTER_TO_INT(data) == GWY_ORIENTATION_HORIZONTAL)
        sym = preset->hsym;
    else
        sym = preset->vsym;
    str = gwy_enum_to_string(sym, symmetries, G_N_ELEMENTS(symmetries));
    g_object_set(renderer, "text", gwy_sgettext(str), NULL);
}

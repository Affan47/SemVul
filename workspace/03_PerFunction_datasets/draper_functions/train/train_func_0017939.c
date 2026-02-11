find_enum_row(GtkTreeModel *model,
              GtkTreeIter *iter,
              gint value)
{
    gint v;

    if (!model || !gtk_tree_model_get_iter_first(model, iter))
        return FALSE;

    do {
        gtk_tree_model_get(model, iter, COMBO_COLUMN_VALUE, &v, -1);
        if (v == value)
            return TRUE;
    } while (gtk_tree_model_iter_next(model, iter));

    return FALSE;
}

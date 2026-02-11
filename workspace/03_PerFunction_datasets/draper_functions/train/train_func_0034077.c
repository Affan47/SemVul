gnc_payment_acct_tree_row_activated_cb (GtkWidget *widget, GtkTreePath *path,
                                        GtkTreeViewColumn *column, PaymentWindow *pw)
{
    GtkTreeView *view;
    GtkTreeModel *model;
    GtkTreeIter iter;

    g_return_if_fail(widget);
    view = GTK_TREE_VIEW(widget);

    model = gtk_tree_view_get_model(view);
    if (gtk_tree_model_get_iter(model, &iter, path))
    {
        if (gtk_tree_model_iter_has_child(model, &iter))
        {


            if (gtk_tree_view_row_expanded(view, path))
                gtk_tree_view_collapse_row(view, path);
            else
                gtk_tree_view_expand_row(view, path, FALSE);
        }
        else

            gnc_payment_ok_cb(widget, pw);
    }
}

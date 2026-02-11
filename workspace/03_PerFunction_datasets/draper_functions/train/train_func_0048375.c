find_by_app (GtkTreeModel *model,
             GtkTreeIter  *iter,
             GspApp       *app)
{
        GspApp *iter_app = NULL;

        if (!gtk_tree_model_get_iter_first (model, iter)) {
                return FALSE;
        }

        do {
                gtk_tree_model_get (model, iter,
                                    STORE_COL_APP, &iter_app,
                                    -1);

                if (iter_app == app) {
                        g_object_unref (iter_app);
                        return TRUE;
                }
        } while (gtk_tree_model_iter_next (model, iter));

        return FALSE;
}

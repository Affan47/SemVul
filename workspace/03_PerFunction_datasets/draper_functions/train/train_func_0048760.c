find_renderer (GtkTreeModel *model,
               const char   *udn,
               GtkTreeIter  *iter)
{
        gboolean found = FALSE;
        gboolean more = TRUE;

        g_assert (udn != NULL);
        g_assert (iter != NULL);

        more = gtk_tree_model_get_iter_first (model, iter);

        while (more) {
                GUPnPDeviceInfo *info;

                gtk_tree_model_get (model,
                                    iter,
                                    2, &info,
                                    -1);

                if (info) {
                        const char *device_udn;

                        device_udn = gupnp_device_info_get_udn (info);

                        if (strcmp (device_udn, udn) == 0)
                                found = TRUE;

                        g_object_unref (info);
                }

                if (found)
                        break;

                more = gtk_tree_model_iter_next (model, iter);
        }

        return found;
}

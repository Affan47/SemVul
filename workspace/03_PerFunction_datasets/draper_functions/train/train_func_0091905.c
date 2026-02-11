gsp_app_manager_get_dir_index (GspAppManager *manager,
                               const char    *dir)
{
        GSList    *l;
        GspXdgDir *xdgdir;

        g_return_val_if_fail (GSP_IS_APP_MANAGER (manager), -1);
        g_return_val_if_fail (dir != NULL, -1);

        for (l = manager->priv->dirs; l != NULL; l = l->next) {
                xdgdir = l->data;
                if (strcmp (dir, xdgdir->dir) == 0) {
                        return xdgdir->index;
                }
        }

        return -1;
}

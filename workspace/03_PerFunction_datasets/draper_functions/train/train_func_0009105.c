gs_manager_set_logout_command (GSManager  *manager,
                               const char *command)
{
        GSList *l;

        g_return_if_fail (GS_IS_MANAGER (manager));

        g_free (manager->priv->logout_command);

        if (command) {
                manager->priv->logout_command = g_strdup (command);
        } else {
                manager->priv->logout_command = NULL;
        }

        for (l = manager->priv->windows; l; l = l->next) {
                gs_window_set_logout_command (l->data, manager->priv->logout_command);
        }
}

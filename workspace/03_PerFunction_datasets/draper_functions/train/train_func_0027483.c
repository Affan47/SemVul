gs_lock_plug_set_logout_command (GSLockPlug *plug,
                                 const char *command)
{
        g_return_if_fail (GS_LOCK_PLUG (plug));

        g_free (plug->priv->logout_command);

        if (command) {
                plug->priv->logout_command = g_strdup (command);
        } else {
                plug->priv->logout_command = NULL;
        }
}

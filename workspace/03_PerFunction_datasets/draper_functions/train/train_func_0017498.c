gsm_shell_finalize (GObject *object)
{
        GsmShell *shell;
        GObjectClass  *parent_class;

        shell = GSM_SHELL (object);

        parent_class = G_OBJECT_CLASS (gsm_shell_parent_class);

        g_object_unref (shell->priv->inhibitors);

        gsm_shell_disconnect_from_bus (shell);

        if (parent_class->finalize != NULL) {
                parent_class->finalize (object);
        }
}

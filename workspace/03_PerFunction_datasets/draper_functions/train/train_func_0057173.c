gitg_shell_finalize (GObject *object)
{
	GitgShell *shell = GITG_SHELL (object);


	gitg_io_cancel (GITG_IO (shell));

	if (shell->priv->cancellable)
	{
		g_object_unref (shell->priv->cancellable);
	}

	G_OBJECT_CLASS (gitg_shell_parent_class)->finalize (object);
}

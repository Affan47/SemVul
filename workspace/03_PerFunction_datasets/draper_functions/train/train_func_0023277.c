giggle_view_shell_get_view_name (GiggleViewShell *shell)
{
	GiggleView *view;

	g_return_val_if_fail (GIGGLE_IS_VIEW_SHELL (shell), NULL);

	view = giggle_view_shell_get_selected (shell);

	if (view)
		return giggle_view_get_name (GIGGLE_VIEW (view));

	return NULL;
}

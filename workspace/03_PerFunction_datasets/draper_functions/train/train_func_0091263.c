on_unload (GeditFileBrowserStore *model,
	   GFile                 *location,
	   GeditFileBrowserView  *view)
{

	if (!view->priv->restore_expand_state || view->priv->is_refresh)
		return;

	remove_expand_state (view, location);
}

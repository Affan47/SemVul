send_pending_changes (EDataCalView *view)
{
	if (view->priv->changes->len == 0)
		return;

	e_gdbus_cal_view_emit_objects_modified (
		view->priv->gdbus_object,
		(const gchar * const *) view->priv->changes->data);
	reset_array (view->priv->changes);
}

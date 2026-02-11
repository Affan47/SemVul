end_not_undoable_action_internal (GtkSourceUndoManagerDefault *manager)
{
	g_return_if_fail (manager->priv->running_not_undoable_actions > 0);

	--manager->priv->running_not_undoable_actions;
}

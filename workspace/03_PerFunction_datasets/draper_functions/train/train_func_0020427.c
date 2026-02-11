impl_dispose (GObject *object)
{
	RBTaskListDisplay *list = RB_TASK_LIST_DISPLAY (object);

	if (list->priv->model != NULL) {
		g_signal_handlers_disconnect_by_func (list->priv->model, task_list_changed_cb, list);
		g_clear_object (&list->priv->model);
	}
	if (list->priv->widgets != NULL) {
		g_array_free (list->priv->widgets, TRUE);
		list->priv->widgets = NULL;
	}
	G_OBJECT_CLASS (rb_task_list_display_parent_class)->dispose (object);
}

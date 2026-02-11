nemo_file_undo_info_apply_async (NemoFileUndoInfo *self,
				     gboolean undo,
				     GtkWindow *parent_window,
				     GAsyncReadyCallback callback,
				     gpointer user_data)
{
	g_assert (self->priv->apply_async_result == NULL);

	self->priv->apply_async_result =
		g_simple_async_result_new (G_OBJECT (self),
					   callback, user_data,
					   nemo_file_undo_info_apply_async);

	if (undo) {
		NEMO_FILE_UNDO_INFO_CLASS (G_OBJECT_GET_CLASS (self))->undo_func (self, parent_window);
	} else {
		NEMO_FILE_UNDO_INFO_CLASS (G_OBJECT_GET_CLASS (self))->redo_func (self, parent_window);
	}
}

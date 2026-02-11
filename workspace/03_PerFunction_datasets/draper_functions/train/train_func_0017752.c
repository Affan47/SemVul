nautilus_file_operation_free (NautilusFileOperation *op)
{
	nautilus_file_operation_remove (op);
	nautilus_file_unref (op->file);
	g_object_unref (op->cancellable);
	if (op->free_data) {
		op->free_data (op->data);
	}

	if (op->undo_info != NULL) {
		nautilus_file_undo_manager_set_action (op->undo_info);
		g_object_unref (op->undo_info);
	}

	g_free (op);
}

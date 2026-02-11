message_view_serialize (MessageView *view, AnjutaSerializer *serializer)
{
	GtkTreeModel *model;
	GtkTreeIter iter;

	g_return_val_if_fail (view != NULL && MESSAGE_IS_VIEW (view), FALSE);

	if (!anjuta_serializer_write_string (serializer, "label",
										 view->privat->label))
		return FALSE;
	if (!anjuta_serializer_write_string (serializer, "pixmap",
										 view->privat->pixmap))
		return FALSE;
	if (!anjuta_serializer_write_int (serializer, "highlite",
									  view->privat->highlite))
		return FALSE;


	model = view->privat->model;

	if (!anjuta_serializer_write_int (serializer, "messages",
									  gtk_tree_model_iter_n_children (model, NULL)))
		return FALSE;

	if (gtk_tree_model_get_iter_first (model, &iter))
	{
		do
		{
			Message *message;
			gtk_tree_model_get (model, &iter, COLUMN_MESSAGE, &message, -1);
			if (message)
			{
				if (!message_serialize (message, serializer))
					return FALSE;
			}
		}
		while (gtk_tree_model_iter_next (model, &iter));
	}
	return TRUE;
}

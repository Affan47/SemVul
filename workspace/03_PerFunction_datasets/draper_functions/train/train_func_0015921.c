nautilus_view_handle_text_drop (NautilusView  *view,
                                const char    *text,
                                const char    *target_uri,
                                GdkDragAction  action,
                                int            x,
                                int            y)
{
	int length;
	char *container_uri;
	GdkPoint pos;
	char *filename;

	if (text == NULL) {
		return;
	}

	g_return_if_fail (action == GDK_ACTION_COPY);

	container_uri = NULL;
	if (target_uri == NULL) {
		container_uri = nautilus_view_get_backing_uri (view);
		g_assert (container_uri != NULL);
	}

	length = strlen (text);

	pos.x = x;
	pos.y = y;
	view_widget_to_file_operation_position (view, &pos);


	filename = get_drop_filename (text);

	nautilus_view_new_file_with_initial_contents (view,
						      target_uri != NULL ? target_uri : container_uri,
						      filename,
						      text,
						      length,
						      &pos);
	g_free (filename);
	g_free (container_uri);
}

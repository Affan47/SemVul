gtk_source_buffer_set_property (GObject      *object,
				guint         prop_id,
				const GValue *value,
				GParamSpec   *pspec)
{
	GtkSourceBuffer *source_buffer;

	g_return_if_fail (GTK_SOURCE_IS_BUFFER (object));

	source_buffer = GTK_SOURCE_BUFFER (object);

	switch (prop_id)
	{
		case PROP_HIGHLIGHT_SYNTAX:
			gtk_source_buffer_set_highlight_syntax (source_buffer,
								g_value_get_boolean (value));
			break;

		case PROP_HIGHLIGHT_MATCHING_BRACKETS:
			gtk_source_buffer_set_highlight_matching_brackets (source_buffer,
									   g_value_get_boolean (value));
			break;

		case PROP_MAX_UNDO_LEVELS:
			gtk_source_buffer_set_max_undo_levels (source_buffer,
							       g_value_get_int (value));
			break;

		case PROP_LANGUAGE:
			gtk_source_buffer_set_language (source_buffer,
							g_value_get_object (value));
			break;

		case PROP_STYLE_SCHEME:
			gtk_source_buffer_set_style_scheme (source_buffer,
							    g_value_get_object (value));
			break;

		case PROP_UNDO_MANAGER:
			gtk_source_buffer_set_undo_manager (source_buffer,
			                                    g_value_get_object (value));
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

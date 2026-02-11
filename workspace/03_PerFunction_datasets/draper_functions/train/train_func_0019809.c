gtk_source_style_get_property (GObject      *object,
			       guint         prop_id,
			       GValue       *value,
			       GParamSpec   *pspec)
{
	GtkSourceStyle *style = GTK_SOURCE_STYLE (object);

	switch (prop_id)
	{
		case PROP_FOREGROUND:
			g_value_set_string (value, style->foreground);
			break;
		case PROP_BACKGROUND:
			g_value_set_string (value, style->background);
			break;
		case PROP_LINE_BACKGROUND:
			g_value_set_string (value, style->line_background);
			break;
		case PROP_BOLD:
			g_value_set_boolean (value, style->bold);
			break;
		case PROP_ITALIC:
			g_value_set_boolean (value, style->italic);
			break;
		case PROP_UNDERLINE:
			g_value_set_boolean (value, style->underline);
			break;
		case PROP_STRIKETHROUGH:
			g_value_set_boolean (value, style->strikethrough);
			break;

		case PROP_FOREGROUND_SET:
			GET_MASK (style, value, FOREGROUND);
			break;
		case PROP_BACKGROUND_SET:
			GET_MASK (style, value, BACKGROUND);
			break;
		case PROP_LINE_BACKGROUND_SET:
			GET_MASK (style, value, LINE_BACKGROUND);
			break;
		case PROP_BOLD_SET:
			GET_MASK (style, value, BOLD);
			break;
		case PROP_ITALIC_SET:
			GET_MASK (style, value, ITALIC);
			break;
		case PROP_UNDERLINE_SET:
			GET_MASK (style, value, UNDERLINE);
			break;
		case PROP_STRIKETHROUGH_SET:
			GET_MASK (style, value, STRIKETHROUGH);
			break;

		default:
			G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
			break;
	}
}

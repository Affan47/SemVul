document_apply_indent_settings(GeanyDocument *doc)
{
	const GeanyIndentPrefs *iprefs = editor_get_indent_prefs(NULL);
	GeanyIndentType type = iprefs->type;
	gint width = iprefs->width;

	if (iprefs->detect_type && document_detect_indent_type(doc, &type))
	{
		if (type != iprefs->type)
		{
			const gchar *name = NULL;

			switch (type)
			{
				case GEANY_INDENT_TYPE_SPACES:
					name = _("Spaces");
					break;
				case GEANY_INDENT_TYPE_TABS:
					name = _("Tabs");
					break;
				case GEANY_INDENT_TYPE_BOTH:
					name = _("Tabs and Spaces");
					break;
			}


			ui_set_statusbar(TRUE, _("Setting %s indentation mode for %s."), name,
				DOC_FILENAME(doc));
		}
	}
	else if (doc->file_type->indent_type > -1)
		type = doc->file_type->indent_type;

	if (iprefs->detect_width && detect_indent_width(doc->editor, type, &width))
	{
		if (width != iprefs->width)
		{
			ui_set_statusbar(TRUE, _("Setting indentation width to %d for %s."), width,
				DOC_FILENAME(doc));
		}
	}
	else if (doc->file_type->indent_width > -1)
		width = doc->file_type->indent_width;

	editor_set_indent(doc->editor, type, width);
}

set_base_and_text (char const *type_name)
{
	static char const *_text_widgets[] = { "GtkCellView", "GtkEntry",
						"GtkTextView" };

	for (unsigned int i = 0; i < G_N_ELEMENTS (_text_widgets); i++) {
		if (0 == g_strcmp0 (type_name, _text_widgets[i])) {
			return true;
		}
	}

	return false;
}

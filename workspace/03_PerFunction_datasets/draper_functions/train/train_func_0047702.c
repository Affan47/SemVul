prefs_set_text(PrefParam *pparam)
{
	gchar *buf, *sp, *bufp;
	gchar **str;
	GtkTextView *text;
	GtkTextBuffer *buffer;
	GtkTextIter iter;

	cm_return_if_fail(*pparam->widget != NULL);

	switch (pparam->type) {
	case P_STRING:
	case P_PASSWORD:
		str = (gchar **)pparam->data;
		if (*str) {
			bufp = buf = alloca(strlen(*str) + 1);
			if (!buf) buf = "";
			else {
				sp = *str;
				while (*sp) {
					if (*sp == '\\' && *(sp + 1) == 'n') {
						*bufp++ = '\n';
						sp += 2;
					} else
						*bufp++ = *sp++;
				}
				*bufp = '\0';
			}
		} else
			buf = "";

		text = GTK_TEXT_VIEW(*pparam->widget);
		buffer = gtk_text_view_get_buffer(text);
		gtk_text_buffer_set_text(buffer, "", -1);
		gtk_text_buffer_get_start_iter(buffer, &iter);
		gtk_text_buffer_insert(buffer, &iter, buf, -1);
		break;
	default:
		g_warning("Invalid PrefType for GtkTextView widget: %d\n",
			  pparam->type);
	}
}

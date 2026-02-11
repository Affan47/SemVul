extract_text_node (const gchar *text,
		   gint        *n)
{
	glTextNode *text_node;
	gchar      *p;
	gint        m;

	text_node = g_new0 (glTextNode, 1);

	if (strncmp (text, "${", strlen ("${")) == 0) {

		text_node->field_flag = TRUE;
		*n = strlen ("${");
		text += *n;
		for (p = (gchar *)text, m = 0; *p != 0; p++, m++, (*n)++) {
			if (*p == '}') {
				(*n)++;
				break;
			}
		}
		text_node->data = g_strndup (text, m);
	} else {

		text_node->field_flag = FALSE;
		for (p = (gchar *)text, *n = 0; *p != 0; p++, (*n)++) {
			if (strncmp (p, "${", strlen ("${")) == 0)
				break;
			if (*p == '\n')
				break;
		}
		text_node->data = g_strndup (text, *n);
	}

	return text_node;
}

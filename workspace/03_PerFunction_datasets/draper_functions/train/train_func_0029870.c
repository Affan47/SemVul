format_get_text_args(TEXT_DEST_REC *dest,
				  const char *text, char **arglist)
{
	GString *out;
	char code, *ret;
	int need_free;

	out = g_string_new(NULL);

	code = 0;
	while (*text != '\0') {
		if (code == '%') {

			if (!format_expand_styles(out, &text, &dest->flags)) {
				g_string_append_c(out, '%');
				g_string_append_c(out, '%');
				g_string_append_c(out, *text);
			}
			code = 0;
		} else if (code == '$') {

			char *ret;

			ret = parse_special((char **) &text, dest->server,
					    dest->target == NULL ? NULL :
					    window_item_find(dest->server, dest->target),
					    arglist, &need_free, NULL, 0);

			if (ret != NULL) {


				int diff;
				int len = strlen(ret);
				while (len > 0 && ret[len-1] == 3) len--;
				diff = strlen(ret)-len;

				g_string_append(out, ret);
				if (diff > 0)
					g_string_truncate(out, out->len-diff);
				if (need_free) g_free(ret);
			}
			code = 0;
		} else {
			if (*text == '%' || *text == '$')
				code = *text;
			else
				g_string_append_c(out, *text);
		}

		text++;
	}

	ret = out->str;
	g_string_free(out, FALSE);
	return ret;
}

im_hangul_get_candidate_string(GtkIMContextHangul *ic)
{
    int n;
    gboolean res;
    gchar* text = NULL;
    gint cursor_index = 0;
    gunichar buf[20] = { 0, };
    char* str = NULL;

    n = G_N_ELEMENTS(buf);
    if (!hangul_ic_is_empty(ic->hic)) {
	const ucschar* preedit;
	int i, preedit_len;

	preedit = hangul_ic_get_preedit_string(ic->hic);
	preedit_len = ucschar_strlen(preedit);

	n -= preedit_len;
	for (i = 0; i < preedit_len; i++) {
	    buf[n + i] = preedit[i];
	}
    }

    res = gtk_im_context_get_surrounding(GTK_IM_CONTEXT(ic),
					 &text, &cursor_index);
    if (res && text != NULL) {
	gchar* p;

	p = g_utf8_find_prev_char(text, text + cursor_index);
	while (n > 0 && p != NULL) {
	    if (*p == ' ')
		break;

	    buf[n - 1] = g_utf8_get_char(p);

	    p = g_utf8_find_prev_char(text, p);
	    n--;
	}

	g_free(text);
    }

    if (n < G_N_ELEMENTS(buf)) {
	char* utf8;
	int len = G_N_ELEMENTS(buf) - n;
	if (ic->candidate_string == NULL) {
	    ic->candidate_string = g_array_sized_new(FALSE, FALSE,
						     sizeof(gunichar), len);
	} else if (ic->candidate_string->len > 0) {
	    g_array_set_size(ic->candidate_string, 0);
	}

	g_array_insert_vals(ic->candidate_string, 0, buf + n, len);
	utf8 = g_ucs4_to_utf8((const gunichar*)ic->candidate_string->data,
			      len, NULL, NULL, NULL);
	str = g_utf8_normalize(utf8, -1, G_NORMALIZE_DEFAULT_COMPOSE);
	g_free(utf8);
    }

    return str;
}

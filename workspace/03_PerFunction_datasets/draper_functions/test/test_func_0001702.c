odf_new_markup (GnmOOExport *state, const PangoAttrList *markup, char const *text)
{
	int handled = 0;
	PangoAttrIterator * iter;
	int from, to;
	int len = text ? strlen (text) : 0;


	gboolean white_written = TRUE;

	if (len == 0)
		return;
	if (markup == NULL) {
		odf_add_chars (state, text, len, &white_written);
		return;
	}

	iter = pango_attr_list_get_iterator ((PangoAttrList *) markup);

	do {
		GSList *list, *l;
		int spans = 0;

		pango_attr_iterator_range (iter, &from, &to);
		to = (to > len) ? len : to;
		from = (from > len) ? len : from;
		if (from > handled)
			odf_add_chars (state, text + handled, from - handled, &white_written);
		list = pango_attr_iterator_get_attrs (iter);
		for (l = list; l != NULL; l = l->next)
			spans += odf_attrs_as_string (state, l->data);
		g_slist_free (list);
		if (to > from) {
			odf_add_chars (state, text + from, to - from, &white_written);
		}
		while (spans-- > 0)
			gsf_xml_out_end_element (state->xml);
		handled = to;
	} while (pango_attr_iterator_next (iter));

	pango_attr_iterator_destroy (iter);

	return;
}

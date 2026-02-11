filter_view_context_item_to_entry(struct filter_view *fv, struct context_item *item)
{
	if (item->items == NULL) {
		gtk_entry_set_text(item->entry, "");
	} else {
		GString *s = g_string_new("");
		size_t i;
		for (i = 0; i < apol_vector_get_size(item->items); i++) {
			char *t = apol_vector_get_element(item->items, i);
			if (i > 0) {
				g_string_append(s, ", ");
			}
			g_string_append(s, t);
		}
		gtk_entry_set_text(item->entry, s->str);
		g_string_free(s, TRUE);
	}
}

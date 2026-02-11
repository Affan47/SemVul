widget_text_init(struct widget_text *w, const char *start_text) {
	if (w->text == NULL)
		w->text = alloc_autostr(10000);
	w->text->length = 0;
	autostr_printf(w->text, "%s", start_text);

	w->mouse_hover = NOT_HOVERED;
	w->mouse_already_handled = 0;
	w->scroll_offset = 0;
	w->line_height_factor = 1.0;
	w->content_above_func = NULL;
	w->content_below_func = NULL;
}

text_width_list(void *ctx, word *text) {
    int w = 0;
    while (text) {
	w += text_width(ctx, text);
	text = text->next;
    }
    return w;
}

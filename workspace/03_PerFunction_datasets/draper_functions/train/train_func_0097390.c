replace(const Arg *arg) {
	Key k = getkey();
	if (!k.str[0])
		return;
	size_t pos = window_cursor_get(vis->win->win);
	action_reset(&action_prev);
	action_prev.op = &ops[OP_REPEAT_REPLACE];
	buffer_put(&buffer_repeat, k.str, strlen(k.str));
	editor_delete_key(vis);
	editor_insert_key(vis, k.str, strlen(k.str));
	text_snapshot(vis->win->text->data);
	window_cursor_to(vis->win->win, pos);
}

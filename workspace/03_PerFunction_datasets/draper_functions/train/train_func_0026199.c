cavan_dialog_init(struct cavan_dialog *dialog, struct cavan_application_context *context, const char *text)
{
	int ret;
	struct cavan_display_rect rect;
	struct cavan_window *body = &dialog->body;
	struct cavan_window *win = &dialog->window;
	struct cavan_window *title = &dialog->title.window;

	ret = cavan_window_init(win, context);
	if (ret < 0)
	{
		return ret;
	}

	ret = cavan_label_init(&dialog->title, context, text);
	if (ret < 0)
	{
		goto out_win_destroy;
	}

	dialog->title.align = CAVAN_WIN_TEXT_ALIGN_CENTER;

	ret = cavan_window_init(&dialog->body, context);
	if (ret < 0)
	{
		goto out_title_destroy;
	}

	dialog->move_able = true;
	dialog->backup = NULL;
	dialog->xofs = dialog->yofs = 0;

	win->border_width = 0;
	win->paint_handler = cavan_dialog_paint_handler;
	win->click_handler = cavan_dialog_click_handler;
	win->move_handler = cavan_dialog_move_handler;

	win->get_rect_handler(win, &rect);

	title->x = 0;
	title->y = 0;
	title->width = rect.width;

	body->x = 0;
	body->width = rect.width;

	cavan_dialog_set_title_height(dialog, title->height);

	cavan_window_add_child(win, title);
	cavan_window_add_child(win, body);

out_title_destroy:
	title->destroy_handler(title);
out_win_destroy:
	win->destroy_handler(win);
	return 0;
}

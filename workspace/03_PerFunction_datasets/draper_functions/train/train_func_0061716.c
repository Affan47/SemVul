hud_query_scrollback_size()
{
	int count = 0, y_add = 0;
	int font_height = gr_get_font_height();
	line_node *ptr;

	if (EMPTY(&Msg_scrollback_used_list) || !HUD_msg_inited)
		return 0;

	ptr = GET_FIRST(&Msg_scrollback_used_list);
	while (ptr != END_OF_LIST(&Msg_scrollback_used_list)) {
		if (ptr->source != HUD_SOURCE_HIDDEN) {
			y_add = ptr->y;
			count += font_height + ptr->y;
		}

		ptr = GET_NEXT(ptr);
	}

	count -= y_add;
	return count;
}

ganv_item_show(GanvItem* item)
{
	g_return_if_fail(GANV_IS_ITEM(item));

	if (!(item->object.flags & GANV_ITEM_VISIBLE)) {
		item->object.flags |= GANV_ITEM_VISIBLE;
		ganv_canvas_base_request_redraw(item->canvas, item->x1, item->y1, item->x2 + 1,
		                                item->y2 + 1);
		item->canvas->need_repick = TRUE;
	}
}

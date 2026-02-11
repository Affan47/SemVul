eel_canvas_item_move (EelCanvasItem *item, double dx, double dy)
{
        g_return_if_fail (item != NULL);
        g_return_if_fail (EEL_IS_CANVAS_ITEM (item));

        if (!EEL_CANVAS_ITEM_GET_CLASS (item)->translate) {
                g_warning ("Item type %s does not implement translate method.\n",
                           g_type_name (G_OBJECT_TYPE (item)));
                return;
        }

        (* EEL_CANVAS_ITEM_GET_CLASS (item)->translate) (item, dx, dy);

	if (item->flags & EEL_CANVAS_ITEM_MAPPED)
		item->canvas->need_repick = TRUE;

	if (!(item->flags & EEL_CANVAS_ITEM_NEED_DEEP_UPDATE)) {
		item->flags |= EEL_CANVAS_ITEM_NEED_DEEP_UPDATE;
		if (item->parent != NULL)
			eel_canvas_item_request_update (item->parent);
		else
			eel_canvas_request_update (item->canvas);
	}

}

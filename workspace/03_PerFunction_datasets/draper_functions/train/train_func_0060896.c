eel_canvas_item_unrealize (EelCanvasItem *item)
{
	if (item->flags & EEL_CANVAS_ITEM_MAPPED)
		(* EEL_CANVAS_ITEM_GET_CLASS (item)->unmap) (item);

	item->flags &= ~(EEL_CANVAS_ITEM_REALIZED);
}

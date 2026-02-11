gnome_canvas_item_request_update (GnomeCanvasItem *item)
{
	if (item->flags & GNOME_CANVAS_ITEM_NEED_UPDATE)
		return;

	item->flags |= GNOME_CANVAS_ITEM_NEED_UPDATE;

	if (item->parent != NULL) {

		gnome_canvas_item_request_update (item->parent);
	} else {


		gnome_canvas_request_update (item->canvas);
	}
}

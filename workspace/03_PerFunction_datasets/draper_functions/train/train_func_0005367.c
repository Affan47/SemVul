nautilus_canvas_item_accessible_get_parent (AtkObject *accessible)
{
	NautilusCanvasItem *item;

	item = NAUTILUS_CANVAS_ITEM (atk_gobject_accessible_get_object (ATK_GOBJECT_ACCESSIBLE (accessible)));
	if (!item) {
		return NULL;
	}

	return gtk_widget_get_accessible (GTK_WIDGET (EEL_CANVAS_ITEM (item)->canvas));
}

gnome_canvas_group_draw (GnomeCanvasItem *item,
                         cairo_t *cr,
                         gint x,
                         gint y,
                         gint width,
                         gint height)
{
	GnomeCanvasGroup *group;
	GList *list;
	GnomeCanvasItem *child = NULL;

	group = GNOME_CANVAS_GROUP (item);

	for (list = group->item_list; list; list = list->next) {
		child = list->data;

		if ((child->flags & GNOME_CANVAS_ITEM_VISIBLE)
		    && ((child->x1 < (x + width))
		    && (child->y1 < (y + height))
		    && (child->x2 > x)
		    && (child->y2 > y))) {
			cairo_save (cr);

			GNOME_CANVAS_ITEM_GET_CLASS (child)->draw (
				child, cr, x, y, width, height);

			cairo_restore (cr);
		}
	}
}

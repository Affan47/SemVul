group_remove (EelCanvasGroup *group, EelCanvasItem *item)
{
	GList *children;

	g_return_if_fail (EEL_IS_CANVAS_GROUP (group));
	g_return_if_fail (EEL_IS_CANVAS_ITEM (item));

	for (children = group->item_list; children; children = children->next)
		if (children->data == item) {
			if (item->flags & EEL_CANVAS_ITEM_MAPPED) {
				(* EEL_CANVAS_ITEM_GET_CLASS (item)->unmap) (item);
			}

			if (item->flags & EEL_CANVAS_ITEM_REALIZED)
				(* EEL_CANVAS_ITEM_GET_CLASS (item)->unrealize) (item);

			if (item->flags & EEL_CANVAS_ITEM_VISIBLE)
				eel_canvas_queue_resize (item->canvas);


			item->parent = NULL;

			g_object_unref (G_OBJECT (item));


			if (children == group->item_list_end)
				group->item_list_end = children->prev;

			group->item_list = g_list_remove_link (group->item_list, children);
			g_list_free (children);
			break;
		}
}

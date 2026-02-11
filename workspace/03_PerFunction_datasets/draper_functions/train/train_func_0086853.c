sheet_object_move_do (GSList *objects, GSList *anchors,
		      gboolean objects_created)
{
	GOUndo *undo = NULL;
	GSList *objs = objects, *anchs = anchors;

	g_return_val_if_fail (NULL != objects, NULL);
	g_return_val_if_fail (NULL != anchors, NULL);
	g_return_val_if_fail (g_slist_length (objects)
			      == g_slist_length (anchors), NULL);

	for (; objs && anchs; objs = objs->next, anchs = anchs->next) {
		SheetObject *obj = objs->data;
		SheetObjectAnchor *anch = anchs->data;
		SheetObjectAnchor *tmp;

		if (objects_created) {
			undo = go_undo_combine
				(undo,
				 go_undo_binary_new
				 (g_object_ref (obj),
				  sheet_object_get_sheet (obj),
				  (GOUndoBinaryFunc) sheet_object_set_sheet,
				  (GFreeFunc) g_object_unref,
				  NULL));
		}
		tmp = g_new (SheetObjectAnchor, 1);
		*tmp = *anch;
		undo = go_undo_combine
			(go_undo_binary_new
			 (g_object_ref (obj), tmp,
			  (GOUndoBinaryFunc) sheet_object_set_anchor,
			  (GFreeFunc) g_object_unref,
			  (GFreeFunc) g_free), undo);
	}
	return undo;
}

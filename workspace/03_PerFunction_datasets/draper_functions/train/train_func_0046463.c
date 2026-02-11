item_cursor_motion (GocItem *item, double x_, double y_)
{
	GnmItemCursor *ic = GNM_ITEM_CURSOR (item);
	gint64 x = x_ * item->canvas->pixels_per_unit, y = y_ * item->canvas->pixels_per_unit;
	ic->last_x = x;
	ic->last_y = y;
	if (ic->drag_button < 0) {
		item_cursor_set_cursor (item->canvas, ic, x, y);
		return TRUE;
	}
	if (ic->style == GNM_ITEM_CURSOR_EXPR_RANGE)
		return FALSE;


	if (wbcg_is_editing (scg_wbcg (ic->scg)))
		return TRUE;
	switch (ic->style) {

	case GNM_ITEM_CURSOR_ANTED:
		g_warning ("Animated cursors should not receive events, "
			   "the point method should preclude that");
		return FALSE;

	case GNM_ITEM_CURSOR_SELECTION:
		return item_cursor_selection_motion (item, x, y);

	case GNM_ITEM_CURSOR_DRAG:
		return item_cursor_drag_motion (ic, x, y);

	case GNM_ITEM_CURSOR_AUTOFILL:
		item_cursor_handle_motion (GNM_ITEM_CURSOR (item), x, y, &cb_autofill_scroll);
		return TRUE;

	default:
		return FALSE;
	}
}

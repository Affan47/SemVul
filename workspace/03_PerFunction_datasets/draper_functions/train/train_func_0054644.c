hit_test (NautilusCanvasItem *canvas_item, EelIRect icon_rect)
{
	NautilusCanvasItemDetails *details;

	details = canvas_item->details;


	if (!eel_irect_hits_irect (canvas_item->details->icon_rect, icon_rect)
	    && (!eel_irect_hits_irect (details->text_rect, icon_rect))) {
		return FALSE;
	}


	if (hit_test_stretch_handle (canvas_item, icon_rect, NULL)) {
		return TRUE;
	}


	if (eel_irect_hits_irect (canvas_item->details->icon_rect, icon_rect)) {
		return TRUE;
	}


	if (eel_irect_hits_irect (details->text_rect, icon_rect)
	    && !canvas_item->details->is_renaming) {
		return TRUE;
	}

	return FALSE;
}

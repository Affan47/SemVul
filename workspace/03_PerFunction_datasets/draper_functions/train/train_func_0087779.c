nemo_icon_canvas_item_invalidate_label_size (NemoIconCanvasItem *item)
{
	if (item->details->editable_text_layout != NULL) {
		pango_layout_context_changed (item->details->editable_text_layout);
	}
	if (item->details->additional_text_layout != NULL) {
		pango_layout_context_changed (item->details->additional_text_layout);
	}
	if (item->details->embedded_text_layout != NULL) {
		pango_layout_context_changed (item->details->embedded_text_layout);
	}
	nemo_icon_canvas_item_invalidate_bounds_cache (item);
	item->details->text_width = -1;
	item->details->text_height = -1;
	item->details->text_height_for_layout = -1;
	item->details->text_height_for_entire_text = -1;
	item->details->editable_text_height = -1;
}

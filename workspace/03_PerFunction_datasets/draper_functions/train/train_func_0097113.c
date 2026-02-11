margin_preview_page_create (PrinterSetupState *state)
{
	double x1, y1, x2, y2;
	double width, height;
	MarginPreviewInfo *pi = &state->preview;
	GOStyle *style;
	MarginPreviewPageAvailableSize margin_available_size;

	margin_preview_page_available_size (state, &margin_available_size);
	gtk_widget_set_size_request (state->preview.canvas, margin_available_size.width, margin_available_size.height);

	width = state->width;
	height = state->height;
	x1 = (margin_available_size.width - PREVIEW_MARGIN_X) / width;
	x2 = (margin_available_size.height - PREVIEW_MARGIN_Y) / height;
	pi->scale = MIN (x1, x2);

	pi->offset_x = (margin_available_size.width - (width  * pi->scale)) / 2;
	pi->offset_y = (margin_available_size.height - (height * pi->scale)) / 2;
	x1 = pi->offset_x;
	y1 = pi->offset_y;
	x2 = pi->offset_x + width * pi->scale;
	y2 = pi->offset_y + height * pi->scale;

	pi->group = goc_item_new (
		goc_canvas_get_root (GOC_CANVAS (pi->canvas)),
		goc_group_get_type (),
		"x", 0.0,
		"y", 0.0,
		NULL);

	style = go_styled_object_get_style (
	        GO_STYLED_OBJECT (goc_item_new (GOC_GROUP (pi->group),
			GOC_TYPE_RECTANGLE,
			"x",		 (double) x1+2,
			"y",		 (double) y1+2,
			"width",	 (double) x2-x1,
			"height",	 (double) y2-y1,
			NULL)));
	style->fill.pattern.back = GO_COLOR_BLACK;
	style->line.color = GO_COLOR_BLACK;
	style->line.width = 1.;

	style = go_styled_object_get_style (
		GO_STYLED_OBJECT (goc_item_new (GOC_GROUP (pi->group),
			GOC_TYPE_RECTANGLE,
			"x",		 (double) x1,
			"y",		 (double) y1,
			"width",	 (double) x2-x1,
			"height",	 (double) y2-y1,
			NULL)));
	style->fill.pattern.back = GO_COLOR_WHITE;
	style->line.color = GO_COLOR_BLACK;
	style->line.width = 1.;

	goc_item_invalidate (pi->group);

	draw_margins (state, x1, y1, x2, y2);
}

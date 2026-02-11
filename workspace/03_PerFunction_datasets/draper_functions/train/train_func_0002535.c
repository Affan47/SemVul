icon_get_data_binder (NemoIcon *icon, gpointer data)
{
	IconGetDataBinderContext *context;
	EelDRect world_rect;
	EelIRect widget_rect;
	char *uri;
	NemoIconContainer *container;

	context = (IconGetDataBinderContext *)data;

	g_assert (NEMO_IS_ICON_CONTAINER (context->iterator_context));

	container = NEMO_ICON_CONTAINER (context->iterator_context);

	world_rect = nemo_icon_canvas_item_get_icon_rectangle (icon->item);

	canvas_rect_world_to_widget (EEL_CANVAS (container), &world_rect, &widget_rect);

	uri = nemo_icon_container_get_icon_uri (container, icon);
	if (uri == NULL) {
		g_warning ("no URI for one of the iterated icons");
		return TRUE;
	}

	widget_rect = eel_irect_offset_by (widget_rect,
		- container->details->dnd_info->drag_info.start_x,
		- container->details->dnd_info->drag_info.start_y);

	widget_rect = eel_irect_scale_by (widget_rect,
		1 / EEL_CANVAS (container)->pixels_per_unit);


	context->iteratee (uri,
			   (int) widget_rect.x0,
			   (int) widget_rect.y0,
			   widget_rect.x1 - widget_rect.x0,
			   widget_rect.y1 - widget_rect.y0,
			   context->iteratee_data);

	g_free (uri);

	return TRUE;
}

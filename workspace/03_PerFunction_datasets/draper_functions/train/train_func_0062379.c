nautilus_canvas_container_position_shadow (NautilusCanvasContainer *container,
					 int x, int y)
{
	EelCanvasItem *shadow;
	double world_x, world_y;

	shadow = container->details->dnd_info->shadow;
	if (shadow == NULL) {
		return;
	}

	canvas_widget_to_world (EEL_CANVAS (container), x, y,
				&world_x, &world_y);

	set_shadow_position (shadow, world_x, world_y);
	eel_canvas_item_show (shadow);
}

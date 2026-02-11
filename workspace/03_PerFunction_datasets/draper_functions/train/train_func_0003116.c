icon_set_position (NemoIcon *icon,
		   double x, double y)
{
	NemoIconContainer *container;
	double pixels_per_unit;
	int container_left, container_top, container_right, container_bottom;
	int x1, x2, y1, y2;
	int container_x, container_y, container_width, container_height;
	EelDRect icon_bounds;
	int item_width, item_height;
	int height_above, width_left;
	int min_x, max_x, min_y, max_y;

	if (icon->x == x && icon->y == y) {
		return;
	}

	container = NEMO_ICON_CONTAINER (EEL_CANVAS_ITEM (icon->item)->canvas);

	if (icon == get_icon_being_renamed (container)) {
		end_renaming_mode (container, TRUE);
	}

	if (nemo_icon_container_get_is_fixed_size (container)) {


		container_x = 0;
		container_y = 0;
		container_width = gdk_screen_width () - container_x
			- container->details->left_margin
			- container->details->right_margin;
		container_height = gdk_screen_height () - container_y
			- container->details->top_margin
			- container->details->bottom_margin;
		pixels_per_unit = EEL_CANVAS (container)->pixels_per_unit;

		container_left = container_x / pixels_per_unit;
		container_top =  container_y / pixels_per_unit;
		container_right = container_left + container_width / pixels_per_unit;
		container_bottom = container_top + container_height / pixels_per_unit;

		icon_get_bounding_box (icon, &x1, &y1, &x2, &y2,
				       BOUNDS_USAGE_FOR_ENTIRE_ITEM);
		item_width = x2 - x1;
		item_height = y2 - y1;

		icon_bounds = nemo_icon_canvas_item_get_icon_rectangle (icon->item);


		height_above = icon_bounds.y0 - y1;
		width_left = icon_bounds.x0 - x1;

		min_x = container_left + DESKTOP_PAD_HORIZONTAL + width_left;
		max_x = container_right - DESKTOP_PAD_HORIZONTAL - item_width + width_left;
		x = CLAMP (x, min_x, max_x);

		min_y = container_top + height_above + DESKTOP_PAD_VERTICAL;
		max_y = container_bottom - DESKTOP_PAD_VERTICAL - item_height + height_above;
		y = CLAMP (y, min_y, max_y);
	}

	if (icon->x == ICON_UNPOSITIONED_VALUE) {
		icon->x = 0;
	}
	if (icon->y == ICON_UNPOSITIONED_VALUE) {
		icon->y = 0;
	}

	eel_canvas_item_move (EEL_CANVAS_ITEM (icon->item),
				x - icon->x,
				y - icon->y);

	icon->x = x;
	icon->y = y;
}

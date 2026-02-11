snap_position (NemoIconContainer *container,
	       NemoIcon *icon,
	       int *x, int *y)
{
	int center_x;
	int baseline_y;
	int icon_width;
	int icon_height;
	int total_width;
	int total_height;
	EelDRect icon_position;
	GtkAllocation allocation;

	icon_position = nemo_icon_canvas_item_get_icon_rectangle (icon->item);
	icon_width = icon_position.x1 - icon_position.x0;
	icon_height = icon_position.y1 - icon_position.y0;

	gtk_widget_get_allocation (GTK_WIDGET (container), &allocation);
	total_width = CANVAS_WIDTH (container, allocation);
	total_height = CANVAS_HEIGHT (container, allocation);

	if (nemo_icon_container_is_layout_rtl (container))
	    *x = get_mirror_x_position (container, icon, *x);

	if (*x + icon_width / 2 < DESKTOP_PAD_HORIZONTAL + SNAP_SIZE_X) {
		*x = DESKTOP_PAD_HORIZONTAL + SNAP_SIZE_X - icon_width / 2;
	}

	if (*x + icon_width / 2 > total_width - (DESKTOP_PAD_HORIZONTAL + SNAP_SIZE_X)) {
		*x = total_width - (DESKTOP_PAD_HORIZONTAL + SNAP_SIZE_X + (icon_width / 2));
	}

	if (*y + icon_height < DESKTOP_PAD_VERTICAL + SNAP_SIZE_Y) {
		*y = DESKTOP_PAD_VERTICAL + SNAP_SIZE_Y - icon_height;
	}

	if (*y + icon_height > total_height - (DESKTOP_PAD_VERTICAL + SNAP_SIZE_Y)) {
		*y = total_height - (DESKTOP_PAD_VERTICAL + SNAP_SIZE_Y + (icon_height / 2));
	}

	center_x = *x + icon_width / 2;
	*x = SNAP_NEAREST_HORIZONTAL (center_x) - (icon_width / 2);
	if (nemo_icon_container_is_layout_rtl (container)) {
	    *x = get_mirror_x_position (container, icon, *x);
	}


	baseline_y = *y + icon_height;
	baseline_y = SNAP_NEAREST_VERTICAL (baseline_y);
	*y = baseline_y - icon_height;
}

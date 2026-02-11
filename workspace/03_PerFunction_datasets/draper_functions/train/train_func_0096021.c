keyboard_up (NemoIconContainer *container,
	     GdkEventKey *event)
{
	IsBetterIconFunction fallback;

	fallback = NULL;
	if (container->details->auto_layout &&
	    nemo_icon_container_is_layout_vertical (container) &&
	    !is_rectangle_selection_event (event)) {
		if (gtk_widget_get_direction (GTK_WIDGET (container)) == GTK_TEXT_DIR_RTL) {
			fallback = next_column_bottommost;
		} else {
			fallback = previous_column_lowest;
		}
	}


	keyboard_arrow_key (container,
			    event,
			    GTK_DIR_UP,
			    rightmost_in_bottom_row,
			    nemo_icon_container_is_layout_rtl (container) ?
			    rightmost_in_top_row : leftmost_in_top_row,
			    same_column_above_lowest,
			    fallback,
			    NULL,
			    closest_in_90_degrees);
}

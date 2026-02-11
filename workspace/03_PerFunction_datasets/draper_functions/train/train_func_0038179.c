keyboard_icon_reveal_timeout_callback (gpointer data)
{
	NautilusCanvasContainer *container;
	NautilusCanvasIcon *icon;

	container = NAUTILUS_CANVAS_CONTAINER (data);
	icon = container->details->keyboard_icon_to_reveal;

	g_assert (icon != NULL);


	if (icon == container->details->keyboard_focus
	    || icon->is_selected) {
		reveal_icon (container, icon);
	}
	container->details->keyboard_icon_reveal_timer_id = 0;

	return FALSE;
}

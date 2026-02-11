nautilus_canvas_view_update_click_mode (NautilusCanvasView *canvas_view)
{
	NautilusCanvasContainer	*canvas_container;
	int			click_mode;

	canvas_container = get_canvas_container (canvas_view);
	g_assert (canvas_container != NULL);

	click_mode = g_settings_get_enum (nautilus_preferences, NAUTILUS_PREFERENCES_CLICK_POLICY);

	nautilus_canvas_container_set_single_click_mode (canvas_container,
						       click_mode == NAUTILUS_CLICK_POLICY_SINGLE);
}

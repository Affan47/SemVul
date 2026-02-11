add_idle (GnomeCanvas *canvas)
{
	g_return_if_fail (canvas->need_update);

	if (!canvas->idle_id)
		canvas->idle_id = g_idle_add_full (
			CANVAS_IDLE_PRIORITY,
			idle_handler,
			canvas,
			NULL);


}

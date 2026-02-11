route_startstop_cb ()
{
	route.active = !route.active;

	if (route.active)
	{
		route.edit = FALSE;
		route_settarget (-1);
	}
	else
	{

	}
	close_route_window_cb ();
}

xkl_engine_is_window_from_same_toplevel_window(XklEngine * engine,
					       Window win1, Window win2)
{
	Window app1, app2;
	return xkl_engine_find_toplevel_window(engine, win1, &app1) &&
	    xkl_engine_find_toplevel_window(engine, win2, &app2)
	    && app1 == app2;
}

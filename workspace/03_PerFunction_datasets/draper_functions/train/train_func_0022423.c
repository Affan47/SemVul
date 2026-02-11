main_gui_remove_timer(main_gui_timer_cb func)
{
	g_return_if_fail(func);
	g_return_if_fail(timers);

	slist_remove(timers, cast_func_to_pointer(func));
}

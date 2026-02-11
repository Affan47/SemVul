add_exec_time_to_object (GObject *obj, GTimer *timer)
{
	gdouble etime;
	etime = g_timer_elapsed (timer, NULL);
	if (GDA_IS_DATA_SELECT (obj))
		g_object_set (obj, "execution-delay", etime, NULL);
	else if (GDA_IS_SET (obj)) {
		GdaHolder *holder;
		holder = gda_holder_new_inline (G_TYPE_DOUBLE, "EXEC_DELAY", etime);
		gda_set_add_holder ((GdaSet*) obj, holder);
		g_object_unref ((GObject*) holder);
	}
	else
		TO_IMPLEMENT;
}

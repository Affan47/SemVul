new_gauge(struct text_object *obj, char *p, int p_max_size, int usage)
{
	if (!p_max_size)
		return;

	usage = (usage > 255) ? 255 : ((usage < 0) ? 0 : usage);

#ifdef X11
	if (output_methods & TO_X)
		new_gauge_in_x11(obj, p, usage);
	else
#endif
		new_gauge_in_shell(obj, p, p_max_size, usage);
}

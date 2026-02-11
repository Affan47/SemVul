init(Bounds *b)
{
	ht_view::init(b, VO_TRANSPARENT_CHARS | VO_RESIZE, 0);
	VIEW_DEBUG_NAME("ht_status");
	growmode = MK_GM(GMH_FIT, GMV_TOP);
	idle_count = 0;
	analy_ani = 0;
	clear_len = 0;
	format = get_config_string("misc/statusline");

	if (!format) {
		format = strdup(STATUS_DEFAULT_FORMAT);
	}

	render();
	register_idle_object(this);
}

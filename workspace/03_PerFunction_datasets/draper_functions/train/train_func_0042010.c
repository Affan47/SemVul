ensure_timeout (GnomeBG *bg,
		Slide   *slide)
{
	if (!bg->timeout_id) {
		double timeout = get_slide_timeout (slide);
		bg->timeout_id = g_timeout_add_full (
			G_PRIORITY_LOW,
			timeout * 1000, on_timeout, bg, NULL);

	}
}

color(int slot, struct wt_status *s)
{
	const char *c = s->use_color > 0 ? s->color_palette[slot] : "";
	if (slot == WT_STATUS_ONBRANCH && color_is_nil(c))
		c = s->color_palette[WT_STATUS_HEADER];
	return c;
}

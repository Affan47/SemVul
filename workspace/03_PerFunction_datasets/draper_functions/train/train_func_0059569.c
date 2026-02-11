cache_icon(const char* name, Pixmap pm, int w, int h) {
	if(icon_cnt >= MAX_ICON_CACHE)
		icon_cnt = 0;

	if(icons[icon_cnt].p)
		XFreePixmap(dzen.dpy, icons[icon_cnt].p);

	strncpy(icons[icon_cnt].name, name, ARGLEN);
	icons[icon_cnt].w = w;
	icons[icon_cnt].h = h;
	icons[icon_cnt].p = pm;
	icon_cnt++;
}

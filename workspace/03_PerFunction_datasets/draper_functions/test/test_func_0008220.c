wakeup_source_prepare(struct wakeup_source *ws, const char *name)
{
	if (ws) {
		memset(ws, 0, sizeof(*ws));
		ws->name = name;
	}
}

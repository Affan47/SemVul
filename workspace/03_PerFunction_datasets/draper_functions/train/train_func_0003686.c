format_create_dest_tag(TEXT_DEST_REC *dest, void *server,
			    const char *server_tag, const char *target,
			    int level, WINDOW_REC *window)
{
	memset(dest, 0, sizeof(TEXT_DEST_REC));

	dest->server = server;
	dest->server_tag = server != NULL ? SERVER(server)->tag : server_tag;
	dest->target = target;
	dest->level = level;
	dest->window = window != NULL ? window :
		window_find_closest(server, target, level);
}

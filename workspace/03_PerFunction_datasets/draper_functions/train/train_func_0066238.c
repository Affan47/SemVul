ignore_set_config(IGNORE_REC *rec)
{
	CONFIG_NODE *node;
	char *levelstr;

	if (rec->level == 0)
		return;

	node = iconfig_node_traverse("(ignores", TRUE);
	node = config_node_section(node, NULL, NODE_TYPE_BLOCK);

	if (rec->mask != NULL) iconfig_node_set_str(node, "mask", rec->mask);
	if (rec->level) {
		levelstr = bits2level(rec->level);
		iconfig_node_set_str(node, "level", levelstr);
		g_free(levelstr);
	}
	iconfig_node_set_str(node, "pattern", rec->pattern);
	if (rec->exception) iconfig_node_set_bool(node, "exception", TRUE);
	if (rec->regexp) iconfig_node_set_bool(node, "regexp", TRUE);
	if (rec->fullword) iconfig_node_set_bool(node, "fullword", TRUE);
	if (rec->replies) iconfig_node_set_bool(node, "replies", TRUE);
	if (rec->unignore_time != 0)
		iconfig_node_set_int(node, "unignore_time", rec->unignore_time);
	iconfig_node_set_str(node, "servertag", rec->servertag);

	if (rec->channels != NULL && *rec->channels != NULL) {
		node = config_node_section(node, "channels", NODE_TYPE_LIST);
		iconfig_node_add_list(node, rec->channels);
	}
}

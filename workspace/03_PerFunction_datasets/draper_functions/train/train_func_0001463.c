get_canmatch_exten(struct match_char *node)
{

	struct match_char *node2 = node;

	for (node2 = node; node2; node2 = node2->next_char) {
		if (node2->exten) {
#ifdef NEED_DEBUG_HERE
			ast_log(LOG_NOTICE,"CanMatch_exten returns exten %s(%p)\n", node2->exten->exten, node2->exten);
#endif
			return node2->exten;
		}
	}
#ifdef NEED_DEBUG_HERE
	ast_log(LOG_NOTICE,"CanMatch_exten returns NULL, match_char=%s\n", node->x);
#endif
	return 0;
}

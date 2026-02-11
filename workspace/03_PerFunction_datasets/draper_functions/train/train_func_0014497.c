ast_channel_register(const struct ast_channel_tech *tech)
{
	struct chanlist *chan;

	AST_RWLIST_WRLOCK(&backends);

	AST_RWLIST_TRAVERSE(&backends, chan, list) {
		if (!strcasecmp(tech->type, chan->tech->type)) {
			ast_log(LOG_WARNING, "Already have a handler for type '%s'\n", tech->type);
			AST_RWLIST_UNLOCK(&backends);
			return -1;
		}
	}

	if (!(chan = ast_calloc(1, sizeof(*chan)))) {
		AST_RWLIST_UNLOCK(&backends);
		return -1;
	}
	chan->tech = tech;
	AST_RWLIST_INSERT_HEAD(&backends, chan, list);

	ast_debug(1, "Registered handler for '%s' (%s)\n", chan->tech->type, chan->tech->description);

	ast_verb(2, "Registered channel type '%s' (%s)\n", chan->tech->type, chan->tech->description);

	AST_RWLIST_UNLOCK(&backends);

	return 0;
}

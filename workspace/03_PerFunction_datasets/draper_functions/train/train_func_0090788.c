event_config_free(struct event_config *cfg)
{
	struct event_config_entry *entry;

	while ((entry = TAILQ_FIRST(&cfg->entries)) != NULL) {
		TAILQ_REMOVE(&cfg->entries, entry, next);
		event_config_entry_free(entry);
	}
	mm_free(cfg);
}

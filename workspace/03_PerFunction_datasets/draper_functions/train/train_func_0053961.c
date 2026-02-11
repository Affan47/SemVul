cfg_dump(struct gn_cfg_header *config)
{
	struct gn_cfg_header *hdr = config;

	dprintf("Dumping configuration.\n");

	while (hdr) {
		struct gn_cfg_entry *entry = hdr->entries;

		dprintf("[%s]\n", hdr->section);

		while (entry) {
			dprintf("%s = %s\n", entry->key, entry->value);
			entry = entry->next;
		}
		hdr = hdr->next;
	}
}

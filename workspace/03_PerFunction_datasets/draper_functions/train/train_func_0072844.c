jm_log(struct lib_context *lc, struct raid_dev *rd)
{
	unsigned int i;
	struct jm *jm = META(rd, jm);

	log_print(lc, "%s (%s):", rd->di->path, handler);
	P("signature: %c%c", jm, jm->signature,
	  jm->signature[0], jm->signature[1]);
	P("version: %u%u", jm, jm->version,
	  JM_MAJOR_VERSION(jm), JM_MINOR_VERSION(jm));
	DP("checksum: %u", jm, jm->checksum);
	DP("identity: 0x%x", jm, jm->identity);
	DP("base: %u", jm, jm->segment.base);
	DP("range: %u", jm, jm->segment.range);
	DP("range2: %u", jm, jm->segment.range2);
	DP("name: \"%s\"", jm, jm->name);
	DP("name: %u", jm, jm->mode);
	DP("block: %u", jm, jm->block);
	DP("attribute: %u", jm, jm->attribute);

	for (i = 0; i < JM_SPARES; i++)
		P2("spare[%d]: 0x%x", jm, i, jm->spare[i]);

	for (i = 0; i < JM_MEMBERS; i++)
		P2("member[%d]: 0x%x", jm, i, jm->member[i]);
}

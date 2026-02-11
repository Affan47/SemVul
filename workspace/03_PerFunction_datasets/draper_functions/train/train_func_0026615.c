blkid_new_probe(void)
{
	int i;
	blkid_probe pr;

	blkid_init_debug(0);
	pr = calloc(1, sizeof(struct blkid_struct_probe));
	if (!pr)
		return NULL;

	DBG(LOWPROBE, ul_debug("allocate a new probe %p", pr));


	for (i = 0; i < BLKID_NCHAINS; i++) {
		pr->chains[i].driver = chains_drvs[i];
		pr->chains[i].flags = chains_drvs[i]->dflt_flags;
		pr->chains[i].enabled = chains_drvs[i]->dflt_enabled;
	}
	INIT_LIST_HEAD(&pr->buffers);
	INIT_LIST_HEAD(&pr->values);
	return pr;
}

blkid_probe_reset_values(blkid_probe pr)
{
	if (!pr || list_empty(&pr->values))
		return;

	DBG(LOWPROBE, ul_debug("resetting results pr=%p", pr));

	while (!list_empty(&pr->values)) {
		struct blkid_prval *v = list_entry(pr->values.next,
						struct blkid_prval, prvals);
		blkid_probe_free_value(v);
	}

	INIT_LIST_HEAD(&pr->values);
}

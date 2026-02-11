topology_probe(blkid_probe pr, struct blkid_chain *chn)
{
	size_t i;

	if (!pr || chn->idx < -1)
		return -1;

	if (!S_ISBLK(pr->mode))
		return -EINVAL;

	if (chn->binary) {
		DBG(LOWPROBE, ul_debug("initialize topology binary data"));

		if (chn->data)

			memset(chn->data, 0,
					sizeof(struct blkid_struct_topology));
		else {
			chn->data = calloc(1,
					sizeof(struct blkid_struct_topology));
			if (!chn->data)
				return -ENOMEM;
		}
	}

	blkid_probe_chain_reset_values(pr, chn);

	DBG(LOWPROBE, ul_debug("--> starting probing loop [TOPOLOGY idx=%d]",
		chn->idx));

	i = chn->idx < 0 ? 0 : chn->idx + 1U;

	for ( ; i < ARRAY_SIZE(idinfos); i++) {
		const struct blkid_idinfo *id = idinfos[i];

		chn->idx = i;

		if (id->probefunc) {
			DBG(LOWPROBE, ul_debug("%s: call probefunc()", id->name));
			if (id->probefunc(pr, NULL) != 0)
				continue;
		}

		if (!topology_is_complete(pr))
			continue;


		topology_set_logical_sector_size(pr);

		DBG(LOWPROBE, ul_debug("<-- leaving probing loop (type=%s) [TOPOLOGY idx=%d]",
			id->name, chn->idx));
		return BLKID_PROBE_OK;
	}

	DBG(LOWPROBE, ul_debug("<-- leaving probing loop (failed) [TOPOLOGY idx=%d]",
		chn->idx));
	return BLKID_PROBE_NONE;
}

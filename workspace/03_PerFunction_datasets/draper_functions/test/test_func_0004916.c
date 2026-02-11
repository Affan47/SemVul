probe_solaris_pt(blkid_probe pr,
		const struct blkid_idmag *mag __attribute__((__unused__)))
{
	struct solaris_vtoc *l;
	struct solaris_slice *p;
	blkid_parttable tab = NULL;
	blkid_partition parent;
	blkid_partlist ls;
	int i;
	uint16_t nparts;

	l = (struct solaris_vtoc *) blkid_probe_get_sector(pr, SOLARIS_SECTOR);
	if (!l) {
		if (errno)
			return -errno;
		goto nothing;
	}

	if (le32_to_cpu(l->v_version) != 1) {
		DBG(LOWPROBE, ul_debug(
			"WARNING: unsupported solaris x86 version %d, ignore",
			le32_to_cpu(l->v_version)));
		goto nothing;
	}

	if (blkid_partitions_need_typeonly(pr))

		return BLKID_PROBE_OK;

	ls = blkid_probe_get_partlist(pr);
	if (!ls)
		goto nothing;

	parent = blkid_partlist_get_parent(ls);

	tab = blkid_partlist_new_parttable(ls, "solaris", SOLARIS_OFFSET);
	if (!tab)
		goto err;

	nparts = le16_to_cpu(l->v_nparts);
	if (nparts > SOLARIS_MAXPARTITIONS)
		nparts = SOLARIS_MAXPARTITIONS;

	for (i = 1, p = &l->v_slice[0];	i < nparts; i++, p++) {

		uint32_t start = le32_to_cpu(p->s_start);
		uint32_t size = le32_to_cpu(p->s_size);
		blkid_partition par;

		if (size == 0 || le16_to_cpu(p->s_tag) == SOLARIS_TAG_WHOLEDISK)
			continue;

		if (parent)


			start += blkid_partition_get_start(parent);

		if (parent && !blkid_is_nested_dimension(parent, start, size)) {
			DBG(LOWPROBE, ul_debug(
				"WARNING: solaris partition (%d) overflow "
				"detected, ignore", i));
			continue;
		}

		par = blkid_partlist_add_partition(ls, tab, start, size);
		if (!par)
			goto err;

		blkid_partition_set_type(par, le16_to_cpu(p->s_tag));
		blkid_partition_set_flags(par, le16_to_cpu(p->s_flag));
	}

	return BLKID_PROBE_OK;

nothing:
	return BLKID_PROBE_NONE;
err:
	return -ENOMEM;
}

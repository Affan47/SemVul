_add_sg_continuation_descriptor(struct osd_request *or,
	const struct osd_sg_entry *sglist, unsigned numentries, u64 *len)
{
	struct osd_sg_continuation_descriptor *oscd;
	u32 oscd_size;
	unsigned i;
	int ret;

	oscd_size = sizeof(*oscd) + numentries * sizeof(oscd->entries[0]);

	if (!or->cdb_cont.total_bytes) {


		or->cdb_cont.total_bytes =
				sizeof(struct osd_continuation_segment_header);
	}

	ret = _alloc_cdb_cont(or, or->cdb_cont.total_bytes + oscd_size);
	if (unlikely(ret))
		return ret;

	oscd = or->cdb_cont.buff + or->cdb_cont.total_bytes;
	oscd->hdr.type = cpu_to_be16(SCATTER_GATHER_LIST);
	oscd->hdr.pad_length = 0;
	oscd->hdr.length = cpu_to_be32(oscd_size - sizeof(*oscd));

	*len = 0;

	for (i = 0; i < numentries; i++) {
		oscd->entries[i].offset = cpu_to_be64(sglist[i].offset);
		oscd->entries[i].len    = cpu_to_be64(sglist[i].len);
		*len += sglist[i].len;
	}

	or->cdb_cont.total_bytes += oscd_size;
	OSD_DEBUG("total_bytes=%d oscd_size=%d numentries=%d\n",
		  or->cdb_cont.total_bytes, oscd_size, numentries);
	return 0;
}

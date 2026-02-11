probe_bcache (blkid_probe pr, const struct blkid_idmag *mag)
{
	struct bcache_super_block *bcs;

	bcs = blkid_probe_get_sb(pr, mag, struct bcache_super_block);
	if (!bcs)
		return errno ? -errno : BLKID_PROBE_NONE;

	if (le64_to_cpu(bcs->offset) != BCACHE_SB_OFF / 512)
		return BLKID_PROBE_NONE;
	if (le16_to_cpu(bcs->keys) > SB_JOURNAL_BUCKETS)
		return BLKID_PROBE_NONE;
	if (!blkid_probe_verify_csum(pr, bcache_crc64(bcs), le64_to_cpu(bcs->csum)))
		return BLKID_PROBE_NONE;

	if (blkid_probe_set_uuid(pr, bcs->uuid) < 0)
		return BLKID_PROBE_NONE;

	return BLKID_PROBE_OK;
}

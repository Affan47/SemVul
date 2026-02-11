probe_hpfs(blkid_probe pr, const struct blkid_idmag *mag)
{
	struct hpfs_super_block *hs;
	struct hpfs_spare_super *hss;
	struct hpfs_boot_block *hbb;
	uint8_t version;


	hs = blkid_probe_get_sb(pr, mag, struct hpfs_super_block);
	if (!hs)
		return -1;
	version = hs->version;


	hss = (struct hpfs_spare_super *)
			blkid_probe_get_buffer(pr,
				HPFS_SBSPARE_OFFSET,
				sizeof(struct hpfs_spare_super));
	if (!hss)
		return -1;
	if (memcmp(hss->magic, "\x49\x18\x91\xf9", 4) != 0)
		return -1;


	hbb = (struct hpfs_boot_block *)
			blkid_probe_get_buffer(pr,
				0,
				sizeof(struct hpfs_boot_block));
	if (!hbb)
		return -1;
	if (memcmp(hbb->magic, "\x55\xaa", 2) == 0 &&
	    memcmp(hbb->sig_hpfs, "HPFS", 4) == 0 &&
	    hbb->sig_28h == 0x28) {
		blkid_probe_set_label(pr, hbb->vol_label, sizeof(hbb->vol_label));
		blkid_probe_sprintf_uuid(pr,
				hbb->vol_serno, sizeof(hbb->vol_serno),
				"%02X%02X-%02X%02X",
				hbb->vol_serno[3], hbb->vol_serno[2],
				hbb->vol_serno[1], hbb->vol_serno[0]);
	}
	blkid_probe_sprintf_version(pr, "%u", version);

	return 0;
}

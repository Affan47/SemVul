probe_lvm2(blkid_probe pr, const struct blkid_idmag *mag)
{
	int sector = mag->kboff << 1;
	struct lvm2_pv_label_header *label;
	char uuid[LVM2_ID_LEN + 7];
	unsigned char *buf;

	buf = blkid_probe_get_buffer(pr,
			mag->kboff << 10,
			512 + sizeof(struct lvm2_pv_label_header));
	if (!buf)
		return errno ? -errno : 1;


	if (memcmp(buf, "LABELONE", 8) == 0) {
		label = (struct lvm2_pv_label_header *) buf;
	} else if (memcmp(buf + 512, "LABELONE", 8) == 0) {
		label = (struct lvm2_pv_label_header *)(buf + 512);
		sector++;
	} else {
		return 1;
	}

	if (le64_to_cpu(label->sector_xl) != (unsigned) sector)
		return 1;

	if (!blkid_probe_verify_csum(
		pr, lvm2_calc_crc(
			&label->offset_xl, LVM2_LABEL_SIZE -
			((char *) &label->offset_xl - (char *) label)),
			le32_to_cpu(label->crc_xl)))
		return 1;

	format_lvm_uuid(uuid, (char *) label->pv_uuid);
	blkid_probe_sprintf_uuid(pr, label->pv_uuid, sizeof(label->pv_uuid),
			"%s", uuid);


	blkid_probe_set_version(pr, mag->magic);


	blkid_probe_set_wiper(pr, 0, 8 * 1024);

	return 0;
}

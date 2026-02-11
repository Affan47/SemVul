radeon_combios_check_hardcoded_edid(struct radeon_device *rdev)
{
	int edid_info, size;
	struct edid *edid;
	unsigned char *raw;
	edid_info = combios_get_table_offset(rdev->ddev, COMBIOS_HARDCODED_EDID_TABLE);
	if (!edid_info)
		return false;

	raw = rdev->bios + edid_info;
	size = EDID_LENGTH * (raw[0x7e] + 1);
	edid = kmalloc(size, GFP_KERNEL);
	if (edid == NULL)
		return false;

	memcpy((unsigned char *)edid, raw, size);

	if (!drm_edid_is_valid(edid)) {
		kfree(edid);
		return false;
	}

	rdev->mode_info.bios_hardcoded_edid = edid;
	rdev->mode_info.bios_hardcoded_edid_size = size;
	return true;
}

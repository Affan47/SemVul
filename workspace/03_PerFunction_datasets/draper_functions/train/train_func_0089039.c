parse_bit_init_tbl_entry(struct drm_device *dev, struct nvbios *bios, struct bit_entry *bitentry)
{


	struct nouveau_drm *drm = nouveau_drm(dev);

	if (bitentry->length < 14) {
		NV_ERROR(drm, "Do not understand init table\n");
		return -EINVAL;
	}

	parse_script_table_pointers(bios, bitentry->offset);
	return 0;
}

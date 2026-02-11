nouveau_bios_embedded_edid(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	const uint8_t edid_sig[] = {
			0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00 };
	uint16_t offset = 0;
	uint16_t newoffset;
	int searchlen = NV_PROM_SIZE;

	if (bios->fp.edid)
		return bios->fp.edid;

	while (searchlen) {
		newoffset = findstr(&bios->data[offset], searchlen,
								edid_sig, 8);
		if (!newoffset)
			return NULL;
		offset += newoffset;
		if (!nv_cksum(&bios->data[offset], EDID1_LEN))
			break;

		searchlen -= offset;
		offset++;
	}

	NV_INFO(drm, "Found EDID in BIOS\n");

	return bios->fp.edid = &bios->data[offset];
}

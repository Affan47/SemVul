nvbios_npdeTp(struct nvkm_bios *bios, u32 base, struct nvbios_npdeT *info)
{
	u32 data = nvbios_npdeTe(bios, base);
	memset(info, 0x00, sizeof(*info));
	if (data) {
		info->image_size = nvbios_rd16(bios, data + 0x08) * 512;
		info->last = nvbios_rd08(bios, data + 0x0a) & 0x80;
	}
	return data;
}

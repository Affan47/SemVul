nvbios_outp_parse(struct nvkm_bios *bios, u8 idx,
		  u8 *ver, u8 *hdr, u8 *cnt, u8 *len, struct nvbios_outp *info)
{
	u16 data = nvbios_outp_entry(bios, idx, ver, hdr, cnt, len);
	if (data && *hdr >= 0x0a) {
		info->type      = nvbios_rd16(bios, data + 0x00);
		info->mask      = nvbios_rd32(bios, data + 0x02);
		if (*ver <= 0x20)
			info->mask |= 0x00c0;
		info->script[0] = nvbios_rd16(bios, data + 0x06);
		info->script[1] = nvbios_rd16(bios, data + 0x08);
		info->script[2] = 0x0000;
		if (*hdr >= 0x0c)
			info->script[2] = nvbios_rd16(bios, data + 0x0a);
		return data;
	}
	return 0x0000;
}

nvbios_boostEm(struct nvkm_bios *bios, u8 pstate,
	       u8 *ver, u8 *hdr, u8 *cnt, u8 *len, struct nvbios_boostE *info)
{
	u32 data, idx = 0;
	while ((data = nvbios_boostEp(bios, idx++, ver, hdr, cnt, len, info))) {
		if (info->pstate == pstate)
			break;
	}
	return data;
}

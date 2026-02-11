nvbios_volt_entry_parse(struct nvkm_bios *bios, int idx, u8 *ver, u8 *len,
			struct nvbios_volt_entry *info)
{
	u16 volt = nvbios_volt_entry(bios, idx, ver, len);
	memset(info, 0x00, sizeof(*info));
	switch (!!volt * *ver) {
	case 0x12:
	case 0x20:
		info->voltage = nvbios_rd08(bios, volt + 0x00) * 10000;
		info->vid     = nvbios_rd08(bios, volt + 0x01);
		break;
	case 0x30:
		info->voltage = nvbios_rd08(bios, volt + 0x00) * 10000;
		info->vid     = nvbios_rd08(bios, volt + 0x01) >> 2;
		break;
	case 0x40:
	case 0x50:
		break;
	}
	return volt;
}

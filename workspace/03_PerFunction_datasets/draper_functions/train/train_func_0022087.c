nv50_gpio_reset(struct nvkm_gpio *gpio, u8 match)
{
	struct nvkm_device *device = gpio->subdev.device;
	struct nvkm_bios *bios = device->bios;
	u8 ver, len;
	u16 entry;
	int ent = -1;

	while ((entry = dcb_gpio_entry(bios, 0, ++ent, &ver, &len))) {
		static const u32 regs[] = { 0xe100, 0xe28c };
		u32 data = nvbios_rd32(bios, entry);
		u8  line =   (data & 0x0000001f);
		u8  func =   (data & 0x0000ff00) >> 8;
		u8  defs = !!(data & 0x01000000);
		u8  unk0 = !!(data & 0x02000000);
		u8  unk1 = !!(data & 0x04000000);
		u32 val = (unk1 << 16) | unk0;
		u32 reg = regs[line >> 4];
		u32 lsh = line & 0x0f;

		if ( func  == DCB_GPIO_UNUSED ||
		    (match != DCB_GPIO_UNUSED && match != func))
			continue;

		nvkm_gpio_set(gpio, 0, func, line, defs);

		nvkm_mask(device, reg, 0x00010001 << lsh, val << lsh);
	}
}

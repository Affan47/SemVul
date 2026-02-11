prom_init(struct nvkm_bios *bios, const char *name)
{
	struct nvkm_device *device = bios->subdev.device;
	if (device->card_type == NV_40 && device->chipset >= 0x4c)
		return ERR_PTR(-ENODEV);
	nvkm_pci_rom_shadow(device->pci, false);
	return device;
}

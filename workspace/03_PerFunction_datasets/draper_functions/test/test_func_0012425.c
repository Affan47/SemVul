nvkm_xtensa_intr(struct nvkm_engine *engine)
{
	struct nvkm_xtensa *xtensa = nvkm_xtensa(engine);
	struct nvkm_subdev *subdev = &xtensa->engine.subdev;
	struct nvkm_device *device = subdev->device;
	const u32 base = xtensa->addr;
	u32 unk104 = nvkm_rd32(device, base + 0xd04);
	u32 intr = nvkm_rd32(device, base + 0xc20);
	u32 chan = nvkm_rd32(device, base + 0xc28);
	u32 unk10c = nvkm_rd32(device, base + 0xd0c);

	if (intr & 0x10)
		nvkm_warn(subdev, "Watchdog interrupt, engine hung.\n");
	nvkm_wr32(device, base + 0xc20, intr);
	intr = nvkm_rd32(device, base + 0xc20);
	if (unk104 == 0x10001 && unk10c == 0x200 && chan && !intr) {
		nvkm_debug(subdev, "Enabling FIFO_CTRL\n");
		nvkm_mask(device, xtensa->addr + 0xd94, 0, xtensa->func->fifo_val);
	}
}

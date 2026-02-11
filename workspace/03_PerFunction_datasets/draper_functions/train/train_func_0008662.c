pramin_read(void *data, u32 offset, u32 length, struct nvkm_bios *bios)
{
	struct nvkm_device *device = bios->subdev.device;
	u32 i;
	if (offset + length <= 0x00100000) {
		for (i = offset; i < offset + length; i += 4)
			*(u32 *)&bios->data[i] = nvkm_rd32(device, 0x700000 + i);
		return length;
	}
	return 0;
}

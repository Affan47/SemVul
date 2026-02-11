nv40_fifo_init(struct nvkm_fifo *base)
{
	struct nv04_fifo *fifo = nv04_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	struct nvkm_fb *fb = device->fb;
	struct nvkm_instmem *imem = device->imem;
	struct nvkm_ramht *ramht = imem->ramht;
	struct nvkm_memory *ramro = imem->ramro;
	struct nvkm_memory *ramfc = imem->ramfc;

	nvkm_wr32(device, 0x002040, 0x000000ff);
	nvkm_wr32(device, 0x002044, 0x2101ffff);
	nvkm_wr32(device, 0x002058, 0x00000001);

	nvkm_wr32(device, NV03_PFIFO_RAMHT, (0x03 << 24)  |
					    ((ramht->bits - 9) << 16) |
					    (ramht->gpuobj->addr >> 8));
	nvkm_wr32(device, NV03_PFIFO_RAMRO, nvkm_memory_addr(ramro) >> 8);

	switch (device->chipset) {
	case 0x47:
	case 0x49:
	case 0x4b:
		nvkm_wr32(device, 0x002230, 0x00000001);
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x45:
	case 0x48:
		nvkm_wr32(device, 0x002220, 0x00030002);
		break;
	default:
		nvkm_wr32(device, 0x002230, 0x00000000);
		nvkm_wr32(device, 0x002220, ((fb->ram->size - 512 * 1024 +
					      nvkm_memory_addr(ramfc)) >> 16) |
					    0x00030000);
		break;
	}

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH1, fifo->base.nr - 1);

	nvkm_wr32(device, NV03_PFIFO_INTR_0, 0xffffffff);
	nvkm_wr32(device, NV03_PFIFO_INTR_EN_0, 0xffffffff);

	nvkm_wr32(device, NV03_PFIFO_CACHE1_PUSH0, 1);
	nvkm_wr32(device, NV04_PFIFO_CACHE1_PULL0, 1);
	nvkm_wr32(device, NV03_PFIFO_CACHES, 1);
}

gf100_fifo_engine(struct gf100_fifo *fifo, u32 engn)
{
	struct nvkm_device *device = fifo->base.engine.subdev.device;

	switch (engn) {
	case 0: engn = NVKM_ENGINE_GR; break;
	case 1: engn = NVKM_ENGINE_MSVLD; break;
	case 2: engn = NVKM_ENGINE_MSPPP; break;
	case 3: engn = NVKM_ENGINE_MSPDEC; break;
	case 4: engn = NVKM_ENGINE_CE0; break;
	case 5: engn = NVKM_ENGINE_CE1; break;
	default:
		return NULL;
	}

	return nvkm_device_engine(device, engn);
}

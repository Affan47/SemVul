nv50_fifo_chan_engine_addr(struct nvkm_engine *engine)
{
	switch (engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW    : return -1;
	case NVKM_ENGINE_GR    : return 0x0000;
	case NVKM_ENGINE_MPEG  : return 0x0060;
	default:
		WARN_ON(1);
		return -1;
	}
}

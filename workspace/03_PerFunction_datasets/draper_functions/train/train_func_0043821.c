nv50_fifo_oneinit(struct nvkm_fifo *base)
{
	struct nv50_fifo *fifo = nv50_fifo(base);
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	int ret;

	ret = nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			      false, &fifo->runlist[0]);
	if (ret)
		return ret;

	return nvkm_memory_new(device, NVKM_MEM_TARGET_INST, 128 * 4, 0x1000,
			       false, &fifo->runlist[1]);
}

gt215_clk_post(struct nvkm_clk *clk, unsigned long *flags)
{
	struct nvkm_device *device = clk->subdev.device;
	struct nvkm_fifo *fifo = device->fifo;

	if (fifo && flags)
		nvkm_fifo_start(fifo, flags);

	nvkm_mask(device, 0x002504, 0x00000001, 0x00000000);
	nvkm_mask(device, 0x020060, 0x00070000, 0x00040000);
}

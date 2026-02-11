gk104_fifo_new_(const struct nvkm_fifo_func *func, struct nvkm_device *device,
		int index, int nr, struct nvkm_fifo **pfifo)
{
	struct gk104_fifo *fifo;

	if (!(fifo = kzalloc(sizeof(*fifo), GFP_KERNEL)))
		return -ENOMEM;
	INIT_WORK(&fifo->fault, gk104_fifo_recover_work);
	*pfifo = &fifo->base;

	return nvkm_fifo_ctor(func, device, index, nr, &fifo->base);
}

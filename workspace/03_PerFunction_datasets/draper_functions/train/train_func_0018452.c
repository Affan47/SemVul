nv40_fifo_dma_engine_init(struct nvkm_fifo_chan *base,
			  struct nvkm_engine *engine)
{
	struct nv04_fifo_chan *chan = nv04_fifo_chan(base);
	struct nv04_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->base.engine.subdev.device;
	struct nvkm_instmem *imem = device->imem;
	unsigned long flags;
	u32 inst, reg, ctx;
	int chid;

	if (!nv40_fifo_dma_engine(engine, &reg, &ctx))
		return 0;
	inst = chan->engn[engine->subdev.index]->addr >> 4;

	spin_lock_irqsave(&fifo->base.lock, flags);
	nvkm_mask(device, 0x002500, 0x00000001, 0x00000000);

	chid = nvkm_rd32(device, 0x003204) & (fifo->base.nr - 1);
	if (chid == chan->base.chid)
		nvkm_wr32(device, reg, inst);
	nvkm_kmap(imem->ramfc);
	nvkm_wo32(imem->ramfc, chan->ramfc + ctx, inst);
	nvkm_done(imem->ramfc);

	nvkm_mask(device, 0x002500, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&fifo->base.lock, flags);
	return 0;
}

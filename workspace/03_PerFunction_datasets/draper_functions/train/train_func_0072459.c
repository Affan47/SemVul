nv10_gr_chan_fini(struct nvkm_object *object, bool suspend)
{
	struct nv10_gr_chan *chan = nv10_gr_chan(object);
	struct nv10_gr *gr = chan->gr;
	struct nvkm_device *device = gr->base.engine.subdev.device;
	unsigned long flags;

	spin_lock_irqsave(&gr->lock, flags);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000000);
	if (nv10_gr_channel(gr) == chan)
		nv10_gr_unload_context(chan);
	nvkm_mask(device, NV04_PGRAPH_FIFO, 0x00000001, 0x00000001);
	spin_unlock_irqrestore(&gr->lock, flags);
	return 0;
}

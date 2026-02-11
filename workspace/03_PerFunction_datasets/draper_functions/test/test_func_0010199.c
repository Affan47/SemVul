nv04_fifo_dma_object_ctor(struct nvkm_fifo_chan *base,
			  struct nvkm_object *object)
{
	struct nv04_fifo_chan *chan = nv04_fifo_chan(base);
	struct nvkm_instmem *imem = chan->fifo->base.engine.subdev.device->imem;
	u32 context = 0x80000000 | chan->base.chid << 24;
	u32 handle  = object->handle;
	int hash;

	switch (object->engine->subdev.index) {
	case NVKM_ENGINE_DMAOBJ:
	case NVKM_ENGINE_SW    : context |= 0x00000000; break;
	case NVKM_ENGINE_GR    : context |= 0x00010000; break;
	case NVKM_ENGINE_MPEG  : context |= 0x00020000; break;
	default:
		WARN_ON(1);
		return -EINVAL;
	}

	mutex_lock(&chan->fifo->base.engine.subdev.mutex);
	hash = nvkm_ramht_insert(imem->ramht, object, chan->base.chid, 4,
				 handle, context);
	mutex_unlock(&chan->fifo->base.engine.subdev.mutex);
	return hash;
}

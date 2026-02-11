nvkm_fifo_chan_child_get(struct nvkm_object *object, int index,
			 struct nvkm_oclass *oclass)
{
	struct nvkm_fifo_chan *chan = nvkm_fifo_chan(object);
	struct nvkm_fifo *fifo = chan->fifo;
	struct nvkm_device *device = fifo->engine.subdev.device;
	struct nvkm_engine *engine;
	u64 mask = chan->engines;
	int ret, i, c;

	for (; c = 0, i = __ffs64(mask), mask; mask &= ~(1ULL << i)) {
		if (!(engine = nvkm_device_engine(device, i)))
			continue;
		oclass->engine = engine;
		oclass->base.oclass = 0;

		if (engine->func->fifo.sclass) {
			ret = engine->func->fifo.sclass(oclass, index);
			if (oclass->base.oclass) {
				if (!oclass->base.ctor)
					oclass->base.ctor = nvkm_object_new;
				oclass->ctor = nvkm_fifo_chan_child_new;
				return 0;
			}

			index -= ret;
			continue;
		}

		while (engine->func->sclass[c].oclass) {
			if (c++ == index) {
				oclass->base = engine->func->sclass[index];
				if (!oclass->base.ctor)
					oclass->base.ctor = nvkm_object_new;
				oclass->ctor = nvkm_fifo_chan_child_new;
				return 0;
			}
		}
		index -= c;
	}

	return -EINVAL;
}

g84_fifo_chan_engine_fini(struct nvkm_fifo_chan *base,
			  struct nvkm_engine *engine, bool suspend)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	struct nv50_fifo *fifo = chan->fifo;
	struct nvkm_subdev *subdev = &fifo->base.engine.subdev;
	struct nvkm_device *device = subdev->device;
	u32 engn, save;
	int offset;
	bool done;

	offset = g84_fifo_chan_engine_addr(engine);
	if (offset < 0)
		return 0;

	engn = g84_fifo_chan_engine(engine);
	save = nvkm_mask(device, 0x002520, 0x0000003f, 1 << engn);
	nvkm_wr32(device, 0x0032fc, chan->base.inst->addr >> 12);
	done = nvkm_msec(device, 2000,
		if (nvkm_rd32(device, 0x0032fc) != 0xffffffff)
			break;
	) >= 0;
	nvkm_wr32(device, 0x002520, save);
	if (!done) {
		nvkm_error(subdev, "channel %d [%s] unload timeout\n",
			   chan->base.chid, chan->base.object.client->name);
		if (suspend)
			return -EBUSY;
	}

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, offset + 0x00, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x04, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x08, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x0c, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
	nvkm_done(chan->eng);
	return 0;
}

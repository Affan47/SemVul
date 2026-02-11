nv50_fifo_chan_engine_init(struct nvkm_fifo_chan *base,
			   struct nvkm_engine *engine)
{
	struct nv50_fifo_chan *chan = nv50_fifo_chan(base);
	struct nvkm_gpuobj *engn = chan->engn[engine->subdev.index];
	u64 limit, start;
	int offset;

	offset = nv50_fifo_chan_engine_addr(engine);
	if (offset < 0)
		return 0;
	limit = engn->addr + engn->size - 1;
	start = engn->addr;

	nvkm_kmap(chan->eng);
	nvkm_wo32(chan->eng, offset + 0x00, 0x00190000);
	nvkm_wo32(chan->eng, offset + 0x04, lower_32_bits(limit));
	nvkm_wo32(chan->eng, offset + 0x08, lower_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x0c, upper_32_bits(limit) << 24 |
					    upper_32_bits(start));
	nvkm_wo32(chan->eng, offset + 0x10, 0x00000000);
	nvkm_wo32(chan->eng, offset + 0x14, 0x00000000);
	nvkm_done(chan->eng);
	return 0;
}

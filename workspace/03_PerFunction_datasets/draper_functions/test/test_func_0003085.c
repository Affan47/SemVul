nv50_sw_chan_dtor(struct nvkm_sw_chan *base)
{
	struct nv50_sw_chan *chan = nv50_sw_chan(base);
	int i;
	for (i = 0; i < ARRAY_SIZE(chan->vblank.notify); i++)
		nvkm_notify_fini(&chan->vblank.notify[i]);
	return chan;
}

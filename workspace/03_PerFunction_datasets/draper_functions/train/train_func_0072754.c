snd_hdac_stream_init(struct hdac_bus *bus, struct hdac_stream *azx_dev,
			  int idx, int direction, int tag)
{
	azx_dev->bus = bus;

	azx_dev->sd_addr = bus->remap_addr + (0x20 * idx + 0x80);

	azx_dev->sd_int_sta_mask = 1 << idx;
	azx_dev->index = idx;
	azx_dev->direction = direction;
	azx_dev->stream_tag = tag;
	snd_hdac_dsp_lock_init(azx_dev);
	list_add_tail(&azx_dev->list, &bus->stream_list);
}

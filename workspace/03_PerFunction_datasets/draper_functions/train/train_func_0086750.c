find_output_space(int dev, char **buf, int *size)
{
	struct audio_operations *adev = audio_devs[dev];
	struct dma_buffparms *dmap = adev->dmap_out;
	unsigned long active_offs;
	long len, offs;
	int maxfrags;
	int occupied_bytes = (dmap->user_counter % dmap->fragment_size);

	*buf = dmap->raw_buf;
	if (!(maxfrags = DMAbuf_space_in_queue(dev)) && !occupied_bytes)
		return 0;

#ifdef BE_CONSERVATIVE
	active_offs = dmap->byte_counter + dmap->qhead * dmap->fragment_size;
#else
	active_offs = max(DMAbuf_get_buffer_pointer(dev, dmap, DMODE_OUTPUT), 0);

	if (active_offs >= dmap->bytes_in_use)
		active_offs = 0;
	active_offs += dmap->byte_counter;
#endif

	offs = (dmap->user_counter % dmap->bytes_in_use) & ~SAMPLE_ROUNDUP;
	if (offs < 0 || offs >= dmap->bytes_in_use) {
		printk(KERN_ERR "Sound: Got unexpected offs %ld. Giving up.\n", offs);
		printk("Counter = %ld, bytes=%d\n", dmap->user_counter, dmap->bytes_in_use);
		return 0;
	}
	*buf = dmap->raw_buf + offs;

	len = active_offs + dmap->bytes_in_use - dmap->user_counter;

	if ((offs + len) > dmap->bytes_in_use)
		len = dmap->bytes_in_use - offs;
	if (len < 0) {
		return 0;
	}
	if (len > ((maxfrags * dmap->fragment_size) - occupied_bytes))
		len = (maxfrags * dmap->fragment_size) - occupied_bytes;
	*size = len & ~SAMPLE_ROUNDUP;
	return (*size > 0);
}

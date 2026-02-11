snd_hdac_dsp_cleanup(struct hdac_stream *azx_dev,
			  struct snd_dma_buffer *dmab)
{
	struct hdac_bus *bus = azx_dev->bus;

	if (!dmab->area || !azx_dev->locked)
		return;

	snd_hdac_dsp_lock(azx_dev);

	snd_hdac_stream_writel(azx_dev, SD_BDLPL, 0);
	snd_hdac_stream_writel(azx_dev, SD_BDLPU, 0);
	snd_hdac_stream_writel(azx_dev, SD_CTL, 0);
	azx_dev->bufsize = 0;
	azx_dev->period_bytes = 0;
	azx_dev->format_val = 0;

	bus->io_ops->dma_free_pages(bus, dmab);
	dmab->area = NULL;

	spin_lock_irq(&bus->reg_lock);
	azx_dev->locked = false;
	spin_unlock_irq(&bus->reg_lock);
	snd_hdac_dsp_unlock(azx_dev);
}

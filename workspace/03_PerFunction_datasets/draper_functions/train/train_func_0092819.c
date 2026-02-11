hsu_dma_remove(struct hsu_dma_chip *chip)
{
	struct hsu_dma *hsu = chip->hsu;
	unsigned short i;

	dma_async_device_unregister(&hsu->dma);

	for (i = 0; i < hsu->nr_channels; i++) {
		struct hsu_dma_chan *hsuc = &hsu->chan[i];

		tasklet_kill(&hsuc->vchan.task);
	}

	return 0;
}

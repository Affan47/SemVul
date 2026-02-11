dmaengine_pcm_set_runtime_hwparams(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct dmaengine_pcm *pcm = soc_platform_to_pcm(rtd->platform);
	struct device *dma_dev = dmaengine_dma_dev(pcm, substream);
	struct dma_chan *chan = pcm->chan[substream->stream];
	struct snd_dmaengine_dai_dma_data *dma_data;
	struct dma_slave_caps dma_caps;
	struct snd_pcm_hardware hw;
	u32 addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			  BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			  BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	int i, ret;

	if (pcm->config && pcm->config->pcm_hardware)
		return snd_soc_set_runtime_hwparams(substream,
				pcm->config->pcm_hardware);

	dma_data = snd_soc_dai_get_dma_data(rtd->cpu_dai, substream);

	memset(&hw, 0, sizeof(hw));
	hw.info = SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID |
			SNDRV_PCM_INFO_INTERLEAVED;
	hw.periods_min = 2;
	hw.periods_max = UINT_MAX;
	hw.period_bytes_min = 256;
	hw.period_bytes_max = dma_get_max_seg_size(dma_dev);
	hw.buffer_bytes_max = SIZE_MAX;
	hw.fifo_size = dma_data->fifo_size;

	if (pcm->flags & SND_DMAENGINE_PCM_FLAG_NO_RESIDUE)
		hw.info |= SNDRV_PCM_INFO_BATCH;

	ret = dma_get_slave_caps(chan, &dma_caps);
	if (ret == 0) {
		if (dma_caps.cmd_pause)
			hw.info |= SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME;
		if (dma_caps.residue_granularity <= DMA_RESIDUE_GRANULARITY_SEGMENT)
			hw.info |= SNDRV_PCM_INFO_BATCH;

		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			addr_widths = dma_caps.dst_addr_widths;
		else
			addr_widths = dma_caps.src_addr_widths;
	}


	for (i = 0; i <= SNDRV_PCM_FORMAT_LAST; i++) {
		int bits = snd_pcm_format_physical_width(i);


		switch (bits) {
		case 8:
		case 16:
		case 24:
		case 32:
		case 64:
			if (addr_widths & (1 << (bits / 8)))
				hw.formats |= (1LL << i);
			break;
		default:

			break;
		}
	}

	return snd_soc_set_runtime_hwparams(substream, &hw);
}

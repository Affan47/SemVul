atmel_ssc_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	struct atmel_ssc_info *ssc_p = &ssc_info[dai->id];
	struct atmel_pcm_dma_params *dma_params;
	int dir, dir_mask;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	else
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	if (dma_params != NULL) {
		dma_params->ssc = NULL;
		dma_params->substream = NULL;
		ssc_p->dma_params[dir] = NULL;
	}

	dir_mask = 1 << dir;

	spin_lock_irq(&ssc_p->lock);
	ssc_p->dir_mask &= ~dir_mask;
	if (!ssc_p->dir_mask) {
		if (ssc_p->initialized) {
			free_irq(ssc_p->ssc->irq, ssc_p);
			ssc_p->initialized = 0;
		}


		ssc_writel(ssc_p->ssc->regs, CR, SSC_BIT(CR_SWRST));

		ssc_p->cmr_div = ssc_p->tcmr_period = ssc_p->rcmr_period = 0;
	}
	spin_unlock_irq(&ssc_p->lock);


	pr_debug("atmel_ssc_dai: Stopping clock\n");
	clk_disable(ssc_p->ssc->clk);
}

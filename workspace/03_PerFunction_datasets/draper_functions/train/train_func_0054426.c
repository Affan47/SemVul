snd_korg1212_interrupt(int irq, void *dev_id)
{
        u32 doorbellValue;
        struct snd_korg1212 *korg1212 = dev_id;

        doorbellValue = readl(korg1212->inDoorbellPtr);

        if (!doorbellValue)
		return IRQ_NONE;

	spin_lock(&korg1212->lock);

	writel(doorbellValue, korg1212->inDoorbellPtr);

        korg1212->irqcount++;

	korg1212->inIRQ++;

        switch (doorbellValue) {
                case K1212_DB_DSPDownloadDone:
                        K1212_DEBUG_PRINTK("K1212_DEBUG: IRQ DNLD count - %ld, %x, [%s].\n",
					   korg1212->irqcount, doorbellValue,
					   stateName[korg1212->cardState]);
                        if (korg1212->cardState == K1212_STATE_DSP_IN_PROCESS) {
				korg1212->dsp_is_loaded = 1;
				wake_up(&korg1212->wait);
			}
                        break;


                case K1212_DB_DMAERROR:
			K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ DMAE count - %ld, %x, [%s].\n",
						   korg1212->irqcount, doorbellValue,
						   stateName[korg1212->cardState]);
			snd_printk(KERN_ERR "korg1212: DMA Error\n");
			korg1212->errorcnt++;
			korg1212->totalerrorcnt++;
			korg1212->sharedBufferPtr->cardCommand = 0;
			snd_korg1212_setCardState(korg1212, K1212_STATE_ERRORSTOP);
                        break;


                case K1212_DB_CARDSTOPPED:
                        K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ CSTP count - %ld, %x, [%s].\n",
						   korg1212->irqcount, doorbellValue,
						   stateName[korg1212->cardState]);
			korg1212->sharedBufferPtr->cardCommand = 0;
                        break;

                default:
			K1212_DEBUG_PRINTK_VERBOSE("K1212_DEBUG: IRQ DFLT count - %ld, %x, cpos=%d [%s].\n",
			       korg1212->irqcount, doorbellValue,
			       korg1212->currentBuffer, stateName[korg1212->cardState]);
                        if ((korg1212->cardState > K1212_STATE_SETUP) || korg1212->idleMonitorOn) {
                                korg1212->currentBuffer++;

                                if (korg1212->currentBuffer >= kNumBuffers)
                                        korg1212->currentBuffer = 0;

                                if (!korg1212->running)
                                        break;

                                if (korg1212->capture_substream) {
					spin_unlock(&korg1212->lock);
                                        snd_pcm_period_elapsed(korg1212->capture_substream);
					spin_lock(&korg1212->lock);
                                }

                                if (korg1212->playback_substream) {
					spin_unlock(&korg1212->lock);
                                        snd_pcm_period_elapsed(korg1212->playback_substream);
					spin_lock(&korg1212->lock);
                                }
                        }
                        break;
        }

	korg1212->inIRQ--;

	spin_unlock(&korg1212->lock);

	return IRQ_HANDLED;
}

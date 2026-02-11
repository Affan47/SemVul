sb_dsp_unload(struct address_info *hw_config, int sbmpu)
{
	sb_devc *devc;

	devc = audio_devs[hw_config->slots[0]]->devc;

	if (devc && devc->base == hw_config->io_base)
	{
		if ((devc->model & MDL_ESS) && devc->pcibase)
			release_region(devc->pcibase, 8);

		release_region(devc->base, 16);

		if (!(devc->caps & SB_NO_AUDIO))
		{
			sound_free_dma(devc->dma8);
			if (devc->dma16 >= 0)
				sound_free_dma(devc->dma16);
		}
		if (!(devc->caps & SB_NO_AUDIO && devc->caps & SB_NO_MIDI))
		{
			if (devc->irq > 0)
				free_irq(devc->irq, devc);

			sb_mixer_unload(devc);


			if (!sbmpu)
				sound_unload_mididev(devc->my_mididev);
			sound_unload_audiodev(devc->dev);
		}
		kfree(devc);
	}
	else
		release_region(hw_config->io_base, 16);

	kfree(detected_devc);
}

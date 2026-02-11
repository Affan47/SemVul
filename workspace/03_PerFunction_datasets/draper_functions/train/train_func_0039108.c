cs46xx_iec958_post_close (struct snd_cs46xx *chip)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;

	if (snd_BUG_ON(!ins->asynch_tx_scb))
		return -EINVAL;

	ins->spdif_status_out  &= ~DSP_SPDIF_STATUS_PLAYBACK_OPEN;


	cs46xx_poke_via_dsp (chip,SP_SPDOUT_CSUV, ins->spdif_csuv_default);


	if (ins->spdif_pcm_input_scb != NULL) {
		cs46xx_dsp_remove_scb (chip,ins->spdif_pcm_input_scb);
		ins->spdif_pcm_input_scb = NULL;
	}

	cs46xx_dsp_remove_scb (chip,ins->asynch_tx_scb);
	ins->asynch_tx_scb = NULL;


	_dsp_clear_sample_buffer(chip,SPDIFO_IP_OUTPUT_BUFFER1,256);


	if ( ins->spdif_status_out & DSP_SPDIF_STATUS_OUTPUT_ENABLED ) {
		cs46xx_dsp_enable_spdif_out (chip);
	}

	return 0;
}

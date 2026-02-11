cs46xx_dsp_set_dac_volume (struct snd_cs46xx * chip, u16 left, u16 right)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;

	mutex_lock(&chip->spos_mutex);


	scb = ins->master_mix_scb->sub_list_ptr;
	while (scb != ins->the_null_scb) {
		cs46xx_dsp_scb_set_volume (chip,scb,left,right);
		scb = scb->next_scb_ptr;
	}


	scb = ins->rear_mix_scb->sub_list_ptr;
	while (scb != ins->the_null_scb) {
		cs46xx_dsp_scb_set_volume (chip,scb,left,right);
		scb = scb->next_scb_ptr;
	}

	ins->dac_volume_left = left;
	ins->dac_volume_right = right;

	mutex_unlock(&chip->spos_mutex);

	return 0;
}

vx_pcm_prepare(struct snd_pcm_substream *subs)
{
	struct vx_core *chip = snd_pcm_substream_chip(subs);
	struct snd_pcm_runtime *runtime = subs->runtime;
	struct vx_pipe *pipe = runtime->private_data;
	int err, data_mode;


	if (chip->chip_status & VX_STAT_IS_STALE)
		return -EBUSY;

	data_mode = (chip->uer_bits & IEC958_AES0_NONAUDIO) != 0;
	if (data_mode != pipe->data_mode && ! pipe->is_capture) {


		struct vx_rmh rmh;
		snd_printdd(KERN_DEBUG "reopen the pipe with data_mode = %d\n", data_mode);
		vx_init_rmh(&rmh, CMD_FREE_PIPE);
		vx_set_pipe_cmd_params(&rmh, 0, pipe->number, 0);
		if ((err = vx_send_msg(chip, &rmh)) < 0)
			return err;
		vx_init_rmh(&rmh, CMD_RES_PIPE);
		vx_set_pipe_cmd_params(&rmh, 0, pipe->number, pipe->channels);
		if (data_mode)
			rmh.Cmd[0] |= BIT_DATA_MODE;
		if ((err = vx_send_msg(chip, &rmh)) < 0)
			return err;
		pipe->data_mode = data_mode;
	}

	if (chip->pcm_running && chip->freq != runtime->rate) {
		snd_printk(KERN_ERR "vx: cannot set different clock %d "
			   "from the current %d\n", runtime->rate, chip->freq);
		return -EINVAL;
	}
	vx_set_clock(chip, runtime->rate);

	if ((err = vx_set_format(chip, pipe, runtime)) < 0)
		return err;

	if (vx_is_pcmcia(chip)) {
		pipe->align = 2;
	} else {
		pipe->align = 4;
	}

	pipe->buffer_bytes = frames_to_bytes(runtime, runtime->buffer_size);
	pipe->period_bytes = frames_to_bytes(runtime, runtime->period_size);
	pipe->hw_ptr = 0;


	vx_update_pipe_position(chip, runtime, pipe);

	pipe->transferred = 0;
	pipe->position = 0;

	pipe->prepared = 1;

	return 0;
}

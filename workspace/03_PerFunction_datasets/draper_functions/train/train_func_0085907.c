pcxhr_update_audio_pipe_level(struct snd_pcxhr *chip,
					 int capture, int channel)
{
	int err;
	struct pcxhr_rmh rmh;
	struct pcxhr_pipe *pipe;

	if (capture)
		pipe = &chip->capture_pipe[0];
	else
		pipe = &chip->playback_pipe;

	pcxhr_init_rmh(&rmh, CMD_AUDIO_LEVEL_ADJUST);

	pcxhr_set_pipe_cmd_params(&rmh, capture, 0, 0,
				  1 << (channel + pipe->first_audio));


	if (capture) {
		rmh.cmd[0] |= VALID_AUDIO_IO_DIGITAL_LEVEL;


		rmh.cmd[2] = chip->digital_capture_volume[channel];
	} else {
		rmh.cmd[0] |=	VALID_AUDIO_IO_MONITOR_LEVEL |
				VALID_AUDIO_IO_MUTE_MONITOR_1;


		rmh.cmd[2] = chip->monitoring_volume[channel] << 10;
		if (chip->monitoring_active[channel] == 0)
			rmh.cmd[2] |= AUDIO_IO_HAS_MUTE_MONITOR_1;
	}
	rmh.cmd_len = 3;

	err = pcxhr_send_msg(chip->mgr, &rmh);
	if (err < 0) {
		dev_dbg(chip->card->dev,
			"error update_audio_level(%d) err=%x\n",
			   chip->chip_idx, err);
		return -EINVAL;
	}
	return 0;
}

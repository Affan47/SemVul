vx_pcm_update_intr(struct vx_core *chip, unsigned int events)
{
	unsigned int i;
	struct vx_pipe *pipe;

#define EVENT_MASK	(END_OF_BUFFER_EVENTS_PENDING|ASYNC_EVENTS_PENDING)

	if (events & EVENT_MASK) {
		vx_init_rmh(&chip->irq_rmh, CMD_ASYNC);
		if (events & ASYNC_EVENTS_PENDING)
			chip->irq_rmh.Cmd[0] |= 0x00000001;
		if (events & END_OF_BUFFER_EVENTS_PENDING)
			chip->irq_rmh.Cmd[0] |= 0x00000002;

		if (vx_send_msg(chip, &chip->irq_rmh) < 0) {
			snd_printdd(KERN_ERR "msg send error!!\n");
			return;
		}

		i = 1;
		while (i < chip->irq_rmh.LgStat) {
			int p, buf, capture, eob;
			p = chip->irq_rmh.Stat[i] & MASK_FIRST_FIELD;
			capture = (chip->irq_rmh.Stat[i] & 0x400000) ? 1 : 0;
			eob = (chip->irq_rmh.Stat[i] & 0x800000) ? 1 : 0;
			i++;
			if (events & ASYNC_EVENTS_PENDING)
				i++;
			buf = 1;
			if (events & END_OF_BUFFER_EVENTS_PENDING) {
				if (eob)
					buf = chip->irq_rmh.Stat[i];
				i++;
			}
			if (capture)
				continue;
			if (snd_BUG_ON(p < 0 || p >= chip->audio_outs))
				continue;
			pipe = chip->playback_pipes[p];
			if (pipe && pipe->substream) {
				vx_pcm_playback_update(chip, pipe->substream, pipe);
				vx_pcm_playback_transfer(chip, pipe->substream, pipe, buf);
			}
		}
	}


	for (i = 0; i < chip->audio_ins; i++) {
		pipe = chip->capture_pipes[i];
		if (pipe && pipe->substream)
			vx_pcm_capture_update(chip, pipe->substream, pipe);
	}
}

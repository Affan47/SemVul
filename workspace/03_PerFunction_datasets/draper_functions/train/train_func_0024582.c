audio_trigger(struct work_struct *work)
{
	struct tm6000_core *core = container_of(work, struct tm6000_core,
						wq_trigger);
	struct snd_tm6000_card *chip = core->adev;

	if (atomic_read(&core->stream_started)) {
		dprintk(1, "starting capture");
		_tm6000_start_audio_dma(chip);
	} else {
		dprintk(1, "stopping capture");
		_tm6000_stop_audio_dma(chip);
	}
}

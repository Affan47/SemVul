ivtv_s_input(struct file *file, void *fh, unsigned int inp)
{
	struct ivtv *itv = fh2id(fh)->itv;
	v4l2_std_id std;
	int i;

	if (inp >= itv->nof_inputs)
		return -EINVAL;

	if (inp == itv->active_input) {
		IVTV_DEBUG_INFO("Input unchanged\n");
		return 0;
	}

	if (atomic_read(&itv->capturing) > 0) {
		return -EBUSY;
	}

	IVTV_DEBUG_INFO("Changing input from %d to %d\n",
			itv->active_input, inp);

	itv->active_input = inp;


	itv->audio_input = itv->card->video_inputs[inp].audio_index;

	if (itv->card->video_inputs[inp].video_type == IVTV_CARD_INPUT_VID_TUNER)
		std = itv->tuner_std;
	else
		std = V4L2_STD_ALL;
	for (i = 0; i <= IVTV_ENC_STREAM_TYPE_VBI; i++)
		itv->streams[i].vdev.tvnorms = std;


	ivtv_mute(itv);
	ivtv_video_set_io(itv);
	ivtv_audio_set_io(itv);
	ivtv_unmute(itv);

	return 0;
}

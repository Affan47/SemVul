ivtv_get_output(struct ivtv *itv, u16 index, struct v4l2_output *output)
{
	const struct ivtv_card_output *card_output = itv->card->video_outputs + index;

	if (index >= itv->card->nof_outputs)
		return -EINVAL;
	output->index = index;
	strlcpy(output->name, card_output->name, sizeof(output->name));
	output->type = V4L2_OUTPUT_TYPE_ANALOG;
	output->audioset = 1;
	output->std = V4L2_STD_ALL;
	return 0;
}

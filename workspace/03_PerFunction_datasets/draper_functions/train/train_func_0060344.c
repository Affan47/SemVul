testEnumOutputAudio(struct node *node)
{
	struct v4l2_audioout output;
	unsigned o = 0;
	int ret;

	for (;;) {
		memset(&output, 0xff, sizeof(output));
		output.index = o;

		ret = doioctl(node, VIDIOC_ENUMAUDOUT, &output);
		if (ret == ENOTTY)
			return ENOTTY;
		if (ret == EINVAL)
			break;
		if (ret)
			return fail("could not enumerate audio output %d\n", o);
		if (checkOutputAudio(output, o))
			return fail("invalid attributes for audio output %d\n", o);
		node->audio_outputs++;
		o++;
	}

	if (node->audio_outputs && !(node->caps & V4L2_CAP_AUDIO))
		return fail("audio outputs reported, but no CAP_AUDIO set\n");
	return 0;
}

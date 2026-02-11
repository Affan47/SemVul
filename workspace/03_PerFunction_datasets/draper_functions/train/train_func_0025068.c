ivtv_prep_dev(struct ivtv *itv, int type)
{
	struct ivtv_stream *s = &itv->streams[type];
	int num_offset = ivtv_stream_info[type].num_offset;
	int num = itv->instance + ivtv_first_minor + num_offset;


	s->vdev.v4l2_dev = NULL;
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;


	if (type == IVTV_ENC_STREAM_TYPE_RAD && !(itv->v4l2_cap & V4L2_CAP_RADIO))
		return 0;
	if (type >= IVTV_DEC_STREAM_TYPE_MPG && !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		return 0;


	if (ivtv_stream_info[type].dma != PCI_DMA_NONE &&
	    itv->options.kilobytes[type] == 0) {
		IVTV_INFO("Disabled %s device\n", ivtv_stream_info[type].name);
		return 0;
	}

	ivtv_stream_init(itv, type);

	snprintf(s->vdev.name, sizeof(s->vdev.name), "%s %s",
			itv->v4l2_dev.name, s->name);

	s->vdev.num = num;
	s->vdev.v4l2_dev = &itv->v4l2_dev;
	if (ivtv_stream_info[type].v4l2_caps &
			(V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_SLICED_VBI_OUTPUT))
		s->vdev.vfl_dir = VFL_DIR_TX;
	s->vdev.fops = ivtv_stream_info[type].fops;
	s->vdev.ctrl_handler = itv->v4l2_dev.ctrl_handler;
	s->vdev.release = video_device_release_empty;
	s->vdev.tvnorms = V4L2_STD_ALL;
	s->vdev.lock = &itv->serialize_lock;
	if (s->type == IVTV_DEC_STREAM_TYPE_VBI) {
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMAUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMINPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_STD);
	}
	ivtv_set_funcs(&s->vdev);
	return 0;
}

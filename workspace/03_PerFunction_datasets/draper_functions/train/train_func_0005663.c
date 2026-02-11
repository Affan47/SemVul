go7007_v4l2_init(struct go7007 *go)
{
	struct video_device *vdev = &go->vdev;
	int rv;

	mutex_init(&go->serialize_lock);
	mutex_init(&go->queue_lock);

	INIT_LIST_HEAD(&go->vidq_active);
	go->vidq.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	go->vidq.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	go->vidq.ops = &go7007_video_qops;
	go->vidq.mem_ops = &vb2_vmalloc_memops;
	go->vidq.drv_priv = go;
	go->vidq.buf_struct_size = sizeof(struct go7007_buffer);
	go->vidq.timestamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	go->vidq.lock = &go->queue_lock;
	rv = vb2_queue_init(&go->vidq);
	if (rv)
		return rv;
	*vdev = go7007_template;
	vdev->lock = &go->serialize_lock;
	vdev->queue = &go->vidq;
	video_set_drvdata(vdev, go);
	vdev->v4l2_dev = &go->v4l2_dev;
	if (!v4l2_device_has_op(&go->v4l2_dev, video, querystd))
		v4l2_disable_ioctl(vdev, VIDIOC_QUERYSTD);
	if (!(go->board_info->flags & GO7007_BOARD_HAS_TUNER)) {
		v4l2_disable_ioctl(vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(vdev, VIDIOC_G_TUNER);
	} else {
		struct v4l2_frequency f = {
			.type = V4L2_TUNER_ANALOG_TV,
			.frequency = 980,
		};

		call_all(&go->v4l2_dev, tuner, s_frequency, &f);
	}
	if (!(go->board_info->sensor_flags & GO7007_SENSOR_TV)) {
		v4l2_disable_ioctl(vdev, VIDIOC_G_STD);
		v4l2_disable_ioctl(vdev, VIDIOC_S_STD);
		vdev->tvnorms = 0;
	}
	if (go->board_info->sensor_flags & GO7007_SENSOR_SCALING)
		v4l2_disable_ioctl(vdev, VIDIOC_ENUM_FRAMESIZES);
	if (go->board_info->num_aud_inputs == 0) {
		v4l2_disable_ioctl(vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(vdev, VIDIOC_ENUMAUDIO);
	}

	if (go->board_info->sensor_flags & GO7007_SENSOR_SAA7115)
		v4l2_subdev_call(go->sd_video, video, s_crystal_freq,
				SAA7115_FREQ_24_576_MHZ,
				SAA7115_FREQ_FL_APLL | SAA7115_FREQ_FL_UCGC |
				SAA7115_FREQ_FL_DOUBLE_ASCLK);
	go7007_s_input(go);
	if (go->board_info->sensor_flags & GO7007_SENSOR_TV)
		go7007_s_std(go);
	rv = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (rv < 0)
		return rv;
	dev_info(go->dev, "registered device %s [v4l2]\n",
		 video_device_node_name(vdev));

	return 0;
}

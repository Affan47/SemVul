uvc_register_video(struct uvc_device *dev,
		struct uvc_streaming *stream)
{
	struct video_device *vdev = &stream->vdev;
	int ret;


	ret = uvc_queue_init(&stream->queue, stream->type, !uvc_no_drop_param);
	if (ret)
		return ret;


	ret = uvc_video_init(stream);
	if (ret < 0) {
		uvc_printk(KERN_ERR, "Failed to initialize the device "
			"(%d).\n", ret);
		return ret;
	}

	uvc_debugfs_init_stream(stream);


	vdev->v4l2_dev = &dev->vdev;
	vdev->fops = &uvc_fops;
	vdev->ioctl_ops = &uvc_ioctl_ops;
	vdev->release = uvc_release;
	vdev->prio = &stream->chain->prio;
	if (stream->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
		vdev->vfl_dir = VFL_DIR_TX;
	strlcpy(vdev->name, dev->name, sizeof vdev->name);


	video_set_drvdata(vdev, stream);

	ret = video_register_device(vdev, VFL_TYPE_GRABBER, -1);
	if (ret < 0) {
		uvc_printk(KERN_ERR, "Failed to register video device (%d).\n",
			   ret);
		return ret;
	}

	if (stream->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		stream->chain->caps |= V4L2_CAP_VIDEO_CAPTURE;
	else
		stream->chain->caps |= V4L2_CAP_VIDEO_OUTPUT;

	atomic_inc(&dev->nstreams);
	return 0;
}

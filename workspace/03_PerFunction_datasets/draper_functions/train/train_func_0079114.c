vsp1_video_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
	struct v4l2_fh *vfh = file->private_data;
	struct vsp1_video *video = to_vsp1_video(vfh->vdev);

	cap->capabilities = V4L2_CAP_DEVICE_CAPS | V4L2_CAP_STREAMING
			  | V4L2_CAP_VIDEO_CAPTURE_MPLANE
			  | V4L2_CAP_VIDEO_OUTPUT_MPLANE;

	if (video->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		cap->device_caps = V4L2_CAP_VIDEO_CAPTURE_MPLANE
				 | V4L2_CAP_STREAMING;
	else
		cap->device_caps = V4L2_CAP_VIDEO_OUTPUT_MPLANE
				 | V4L2_CAP_STREAMING;

	strlcpy(cap->driver, "vsp1", sizeof(cap->driver));
	strlcpy(cap->card, video->video.name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s",
		 dev_name(video->vsp1->dev));

	return 0;
}

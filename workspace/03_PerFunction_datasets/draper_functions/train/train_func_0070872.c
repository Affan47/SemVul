uvc_v4l2_set_streamparm(struct uvc_streaming *stream,
		struct v4l2_streamparm *parm)
{
	struct uvc_streaming_control probe;
	struct v4l2_fract timeperframe;
	uint32_t interval;
	int ret;

	if (parm->type != stream->type)
		return -EINVAL;

	if (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		timeperframe = parm->parm.capture.timeperframe;
	else
		timeperframe = parm->parm.output.timeperframe;

	interval = uvc_fraction_to_interval(timeperframe.numerator,
		timeperframe.denominator);
	uvc_trace(UVC_TRACE_FORMAT, "Setting frame interval to %u/%u (%u).\n",
		timeperframe.numerator, timeperframe.denominator, interval);

	mutex_lock(&stream->mutex);

	if (uvc_queue_streaming(&stream->queue)) {
		mutex_unlock(&stream->mutex);
		return -EBUSY;
	}

	probe = stream->ctrl;
	probe.dwFrameInterval =
		uvc_try_frame_interval(stream->cur_frame, interval);


	ret = uvc_probe_video(stream, &probe);
	if (ret < 0) {
		mutex_unlock(&stream->mutex);
		return ret;
	}

	stream->ctrl = probe;
	mutex_unlock(&stream->mutex);


	timeperframe.numerator = probe.dwFrameInterval;
	timeperframe.denominator = 10000000;
	uvc_simplify_fraction(&timeperframe.numerator,
		&timeperframe.denominator, 8, 333);

	if (parm->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		parm->parm.capture.timeperframe = timeperframe;
	else
		parm->parm.output.timeperframe = timeperframe;

	return 0;
}

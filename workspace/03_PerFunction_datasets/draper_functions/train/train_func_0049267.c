uvc_probe_video(struct uvc_streaming *stream,
	struct uvc_streaming_control *probe)
{
	struct uvc_streaming_control probe_min, probe_max;
	__u16 bandwidth;
	unsigned int i;
	int ret;


	ret = uvc_set_video_ctrl(stream, probe, 1);
	if (ret < 0)
		goto done;


	if (!(stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX)) {
		ret = uvc_get_video_ctrl(stream, &probe_min, 1, UVC_GET_MIN);
		if (ret < 0)
			goto done;
		ret = uvc_get_video_ctrl(stream, &probe_max, 1, UVC_GET_MAX);
		if (ret < 0)
			goto done;

		probe->wCompQuality = probe_max.wCompQuality;
	}

	for (i = 0; i < 2; ++i) {
		ret = uvc_set_video_ctrl(stream, probe, 1);
		if (ret < 0)
			goto done;
		ret = uvc_get_video_ctrl(stream, probe, 1, UVC_GET_CUR);
		if (ret < 0)
			goto done;

		if (stream->intf->num_altsetting == 1)
			break;

		bandwidth = probe->dwMaxPayloadTransferSize;
		if (bandwidth <= stream->maxpsize)
			break;

		if (stream->dev->quirks & UVC_QUIRK_PROBE_MINMAX) {
			ret = -ENOSPC;
			goto done;
		}


		probe->wKeyFrameRate = probe_min.wKeyFrameRate;
		probe->wPFrameRate = probe_min.wPFrameRate;
		probe->wCompQuality = probe_max.wCompQuality;
		probe->wCompWindowSize = probe_min.wCompWindowSize;
	}

done:
	return ret;
}

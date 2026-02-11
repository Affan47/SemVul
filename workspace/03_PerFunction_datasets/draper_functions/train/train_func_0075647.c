uvc_video_suspend(struct uvc_streaming *stream)
{
	if (!uvc_queue_streaming(&stream->queue))
		return 0;

	stream->frozen = 1;
	uvc_uninit_video(stream, 0);
	usb_set_interface(stream->dev->udev, stream->intfnum, 0);
	return 0;
}

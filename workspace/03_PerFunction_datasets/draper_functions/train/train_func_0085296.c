uvc_video_validate_buffer(const struct uvc_streaming *stream,
				      struct uvc_buffer *buf)
{
	if (stream->ctrl.dwMaxVideoFrameSize != buf->bytesused &&
	    !(stream->cur_format->flags & UVC_FMT_FLAG_COMPRESSED))
		buf->error = 1;
}

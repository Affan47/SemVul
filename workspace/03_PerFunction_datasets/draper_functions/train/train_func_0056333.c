uvc_video_decode_end(struct uvc_streaming *stream,
		struct uvc_buffer *buf, const __u8 *data, int len)
{

	if (data[1] & UVC_STREAM_EOF && buf->bytesused != 0) {
		uvc_trace(UVC_TRACE_FRAME, "Frame complete (EOF found).\n");
		if (data[0] == len)
			uvc_trace(UVC_TRACE_FRAME, "EOF in empty payload.\n");
		buf->state = UVC_BUF_STATE_READY;
		if (stream->dev->quirks & UVC_QUIRK_STREAM_NO_FID)
			stream->last_fid ^= UVC_STREAM_FID;
	}
}

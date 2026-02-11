pvr2_hdw_cx25840_vbi_hack(struct pvr2_hdw *hdw)
{


	struct v4l2_format fmt;
	if (hdw->decoder_client_id != PVR2_CLIENT_ID_CX25840) {

		return;
	}

	pvr2_trace(PVR2_TRACE_INIT,
		   "Module ID %u:"
		   " Executing cx25840 VBI hack",
		   hdw->decoder_client_id);
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_SLICED_VBI_CAPTURE;
	fmt.fmt.sliced.service_lines[0][21] = V4L2_SLICED_CAPTION_525;
	fmt.fmt.sliced.service_lines[1][21] = V4L2_SLICED_CAPTION_525;
	v4l2_device_call_all(&hdw->v4l2_dev, hdw->decoder_client_id,
			     vbi, s_sliced_fmt, &fmt.fmt.sliced);
}

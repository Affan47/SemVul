uvc_queue_setup(struct vb2_queue *vq, const void *parg,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], void *alloc_ctxs[])
{
	const struct v4l2_format *fmt = parg;
	struct uvc_video_queue *queue = vb2_get_drv_priv(vq);
	struct uvc_streaming *stream = uvc_queue_to_stream(queue);


	if (fmt && fmt->fmt.pix.sizeimage < stream->ctrl.dwMaxVideoFrameSize)
		return -EINVAL;

	*nplanes = 1;

	sizes[0] = fmt ? fmt->fmt.pix.sizeimage
		 : stream->ctrl.dwMaxVideoFrameSize;

	return 0;
}

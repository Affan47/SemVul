vidioc_reqbufs(struct file *file, void *__fh, struct v4l2_requestbuffers *b)
{
	struct saa7146_fh *fh = __fh;

	if (b->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return videobuf_reqbufs(&fh->video_q, b);
	if (b->type == V4L2_BUF_TYPE_VBI_CAPTURE)
		return videobuf_reqbufs(&fh->vbi_q, b);
	return -EINVAL;
}

vbiMethodsChanged(int idx)
{
	m_buftype = isSlicedVbi() ? V4L2_BUF_TYPE_SLICED_VBI_CAPTURE :
		(isVbi() ? V4L2_BUF_TYPE_VBI_CAPTURE : V4L2_BUF_TYPE_VIDEO_CAPTURE);
}

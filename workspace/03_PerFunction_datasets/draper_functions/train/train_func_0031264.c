dqbuf_mmap_out(v4l2_buffer &buf)
{
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_MMAP;
	return ioctl("dqbuf", VIDIOC_DQBUF, &buf);
}

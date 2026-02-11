dqbuf_mmap(v4l2_buffer &buf, __u32 buftype, bool &again)
{
	int res;

	memset(&buf, 0, sizeof(buf));
	buf.type = buftype;
	buf.memory = V4L2_MEMORY_MMAP;
	res = ioctl(VIDIOC_DQBUF, &buf);
	again = res < 0 && errno == EAGAIN;
	return res >= 0 || again;
}

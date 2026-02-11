src_v4l2_grab(src_t *src)
{
	src_v4l2_t *s = (src_v4l2_t *) src->state;

	if(src->timeout)
	{
		fd_set fds;
		struct timeval tv;
		int r;


		FD_ZERO(&fds);
		FD_SET(s->fd, &fds);

		tv.tv_sec = src->timeout;
		tv.tv_usec = 0;

		r = select(s->fd + 1, &fds, NULL, NULL, &tv);

		if(r == -1)
		{
			ERROR("select: %s", strerror(errno));
			return(-1);
		}

		if(!r)
		{
			ERROR("Timed out waiting for frame!");
			return(-1);
		}
	}

	if(s->map)
	{
		if(s->pframe >= 0)
		{
			if(ioctl(s->fd, VIDIOC_QBUF, &s->buf) == -1)
			{
				ERROR("VIDIOC_QBUF: %s", strerror(errno));
				return(-1);
			}
		}

		memset(&s->buf, 0, sizeof(s->buf));

		s->buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		s->buf.memory = V4L2_MEMORY_MMAP;

		if(ioctl(s->fd, VIDIOC_DQBUF, &s->buf) == -1)
		{
			ERROR("VIDIOC_DQBUF: %s", strerror(errno));
			return(-1);
		}

		src->img    = s->buffer[s->buf.index].start;
		src->length = s->buffer[s->buf.index].length;

		s->pframe = s->buf.index;
	}
	else
	{
		ssize_t r;

		r = read(s->fd, s->buffer[0].start, s->buffer[0].length);
		if(r <= 0)
		{
			ERROR("Unable to read a frame.");
			ERROR("read: %s", strerror(errno));
			return(-1);
		}

		src->img = s->buffer[0].start;
		src->length = r;
	}

	return(0);
}

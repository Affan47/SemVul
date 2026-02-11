v4l2_close(int fd)
{
	int index, result;

	index = v4l2_get_index(fd);
	if (index == -1)
		return SYS_CLOSE(fd);


	pthread_mutex_lock(&devices[index].stream_lock);
	devices[index].open_count--;
	result = devices[index].open_count != 0;
	pthread_mutex_unlock(&devices[index].stream_lock);

	if (result)
		return 0;

	v4l2_plugin_cleanup(devices[index].plugin_library,
			devices[index].dev_ops_priv,
			devices[index].dev_ops);


	v4l2_unmap_buffers(index);
	if (devices[index].convert_mmap_buf != MAP_FAILED) {
		if (v4l2_buffers_mapped(index)) {
			if (!devices[index].gone)
				V4L2_LOG_WARN("v4l2 mmap buffers still mapped on close()\n");
		} else {
			SYS_MUNMAP(devices[index].convert_mmap_buf,
					devices[index].no_frames * V4L2_FRAME_BUF_SIZE);
		}
		devices[index].convert_mmap_buf = MAP_FAILED;
	}
	v4lconvert_destroy(devices[index].convert);
	free(devices[index].readbuf);
	devices[index].readbuf = NULL;
	devices[index].readbuf_size = 0;


	devices[index].fd = -1;


	do {
		result = SYS_CLOSE(fd);
	} while (result == -1 && errno == EINTR);

	V4L2_LOG("close: %d\n", fd);

	return result;
}

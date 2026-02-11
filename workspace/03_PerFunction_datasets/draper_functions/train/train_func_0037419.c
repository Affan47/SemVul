v4l2_deactivate_read_stream(int index)
{
	int result;

	result = v4l2_streamoff(index);
	if (result)
		return result;


	v4l2_unmap_buffers(index);

	v4l2_unrequest_read_buffers(index);

	devices[index].flags &= ~V4L2_STREAM_CONTROLLED_BY_READ;

	return 0;
}

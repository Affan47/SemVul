GetPosition()
{
	int result;

	if (jumped)
		return jump_point;
	if (read_buf && plugin && the_object && the_object->ready) {
		if (read_buf->start < 0)
			return 0;

		int frame_size = plugin->frame_size(the_object);
		if (frame_size)  {
			result = (read_buf->start + (read_buf->buf->read_index * 4) / frame_size);
			if (result < 0) {
				alsaplayer_error("Found the error!");
			}
			return result;
		} else
			return 0;
	} else {
		return 0;
	}
}

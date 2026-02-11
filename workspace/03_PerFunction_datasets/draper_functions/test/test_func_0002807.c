wav_frame_seek(input_object *obj, int frame)
{
	struct wav_local_data *data;
	int result = 0;
	long position;

	if (!obj)
			return result;
	data = (struct wav_local_data *)obj->local_data;
	if (!data) {
			return result;
	}
	position = (frame * (APLAY_FRAME_SIZE >> (2 - obj->nr_channels)));
	position += data->header_size;
	result = !reader_seek(data->wav_fd, position, SEEK_SET);
	return result;
}

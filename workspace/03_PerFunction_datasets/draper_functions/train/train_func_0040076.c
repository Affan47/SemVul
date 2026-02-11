leave_temp_stream(void)
{
	_temp_level--;
	if (_temp_level > 0)
		return &_temp_stream;

	STREAM_write(_temp_save, _temp_stream.string.buffer, STRING_length(_temp_stream.string.buffer));
	STREAM_close(&_temp_stream);
	return _temp_save;
}

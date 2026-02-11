add_result(EVAL_ANALYZE *result, const char *str, int len)
{
	if ((_analyze_buffer_pos + len) > sizeof(_analyze_buffer))
		flush_result(result);

	if (len > sizeof(_analyze_buffer))
		result->str = GB.AddString(result->str, str, len);
	else
	{
		memcpy(&_analyze_buffer[_analyze_buffer_pos], str, len);
		_analyze_buffer_pos += len;
	}
}

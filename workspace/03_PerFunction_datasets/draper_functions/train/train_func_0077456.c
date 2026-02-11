rdp_write_system_time(STREAM* s, SYSTEM_TIME* system_time)
{
	stream_write_uint16(s, system_time->wYear);
	stream_write_uint16(s, system_time->wMonth);
	stream_write_uint16(s, system_time->wDayOfWeek);
	stream_write_uint16(s, system_time->wDay);
	stream_write_uint16(s, system_time->wHour);
	stream_write_uint16(s, system_time->wMinute);
	stream_write_uint16(s, system_time->wSecond);
	stream_write_uint16(s, system_time->wMilliseconds);
}

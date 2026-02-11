invalidate_buffer(Buffer_t *Buffer, mt_off_t start)
{
	if(_buf_flush(Buffer) < 0)
		return -1;


	Buffer->current = ROUND_DOWN(start, Buffer->sectorSize);
	Buffer->cur_size = 0;
	return 0;
}

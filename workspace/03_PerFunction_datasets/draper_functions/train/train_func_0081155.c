salloc()
{
	char *b = buffers[next_buffer++];
	if(next_buffer >= FM_BUFFERS)
		next_buffer = 0;
	return b;
}

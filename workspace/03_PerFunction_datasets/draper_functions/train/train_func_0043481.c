stream_lof(STREAM *stream, int64_t *len)
{
	struct stat info;


	if (fstat(fileno(FD), &info) < 0)
		return TRUE;

	*len = info.st_size;
  return FALSE;
}

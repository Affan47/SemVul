writestring (int fd, mpg123_string *string)
{
	size_t result, bytes;
	char *ptr = string->p;
	bytes = string->fill ? string->fill-1 : 0;

	while(bytes)
	{
		if((result = write(fd, ptr, bytes)) < 0 && errno != EINTR)
		{
			perror ("writing http string");
			return FALSE;
		}
		else if(result == 0)
		{
			error("write: socket closed unexpectedly");
			return FALSE;
		}
		ptr   += result;
		bytes -= result;
	}
	return TRUE;
}

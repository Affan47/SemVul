printfPQExpBuffer(PQExpBuffer str, const char *fmt,...)
{
	va_list		args;
	size_t		avail;
	int			nprinted;

	resetPQExpBuffer(str);

	if (PQExpBufferBroken(str))
		return;

	for (;;)
	{


		if (str->maxlen > str->len + 16)
		{
			avail = str->maxlen - str->len - 1;
			va_start(args, fmt);
			nprinted = vsnprintf(str->data + str->len, avail,
								 fmt, args);
			va_end(args);


			if (nprinted >= 0 && nprinted < (int) avail - 1)
			{

				str->len += nprinted;
				break;
			}
		}

		if (!enlargePQExpBuffer(str, str->maxlen))
			return;
	}
}

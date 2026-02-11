handle_error (char *args, size_t len)
{
    int something_printed;


    char *p = strchr (args, ' ');
    if (!p)
    {
	error (0, 0, "invalid data from cvs server");
	return;
    }
    ++p;


    len -= p - args;
    something_printed = 0;
    for (; len > 0; --len)
    {
	something_printed = 1;
	putc (*p++, stderr);
    }
    if (something_printed)
	putc ('\n', stderr);
}

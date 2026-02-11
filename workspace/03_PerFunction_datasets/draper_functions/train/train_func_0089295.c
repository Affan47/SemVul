add_from_filter_header()
{
static Buffer buf;

	buf.reset();

	if (*add_from_filter_buf_ptr == '\0')
	{
		from_filter= &add_from_filter_body;
		return ("\n");
	}

	do
	{
		while (*add_from_filter_buf_ptr)
		{
			buf.push ( (unsigned char)*add_from_filter_buf_ptr );
			if ( *add_from_filter_buf_ptr++ == '\n')	break;
		}
	} while ( *add_from_filter_buf_ptr && *add_from_filter_buf_ptr != '\n'
		&& isspace( (unsigned char)*add_from_filter_buf_ptr ));
	buf += '\0';
	return (buf);
}

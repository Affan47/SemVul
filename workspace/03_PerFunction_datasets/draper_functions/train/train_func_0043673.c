NextChar()
{
	if (eof)	return (-1);

int	c;

	for (;;)
	{
		c=msg->get_c();

		if (c < 0)
		{
			eof=1;
			if (lastc != '\n')
			{
				c='\n';
				lastc='\n';
			}
			return (c);
		}

		if (c == '\r')	continue;

		if (c == '\n')
		{
		int	nextc=msg->peek();

			if (nextc == '\r' || nextc == '\n')
			{
				if (mergelines)
					end_headers=msg->tell();
				mergelines=0;
				if (header_only)	eof=1;
				return (c);
			}
			if (mergelines && isspace(nextc))	continue;
		}
		lastc=c;
		return (c);
	}
}

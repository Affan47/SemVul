make_vpacket(unsigned long *body, unsigned long event_type,
	     unsigned long num, va_list ap)
{
	unsigned long *bp = body;


	if (num > FvwmPacketMaxSize)
	{
		num = FvwmPacketMaxSize;
	}
	*(bp++) = START_FLAG;
	*(bp++) = event_type;
	*(bp++) = num+FvwmPacketHeaderSize;
	*(bp++) = fev_get_evtime();

	for (; num > 0; --num)
	{
		*(bp++) = va_arg(ap, unsigned long);
	}

	return body;
}

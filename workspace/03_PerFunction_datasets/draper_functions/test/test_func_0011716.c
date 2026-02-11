update_read_bounds(STREAM* s, ORDER_INFO* orderInfo)
{
	uint8 flags;

	stream_read_uint8(s, flags);

	if (flags & BOUND_DELTA_LEFT)
		stream_read_uint8(s, orderInfo->deltaBoundLeft);
	else if (flags & BOUND_LEFT)
		stream_read_uint16(s, orderInfo->boundLeft);

	if (flags & BOUND_DELTA_TOP)
		stream_read_uint8(s, orderInfo->deltaBoundTop);
	else if (flags & BOUND_TOP)
		stream_read_uint16(s, orderInfo->boundTop);

	if (flags & BOUND_DELTA_RIGHT)
		stream_read_uint8(s, orderInfo->deltaBoundRight);
	else if (flags & BOUND_RIGHT)
		stream_read_uint16(s, orderInfo->boundRight);

	if (flags & BOUND_DELTA_BOTTOM)
		stream_read_uint8(s, orderInfo->deltaBoundBottom);
	else if (flags & BOUND_BOTTOM)
		stream_read_uint16(s, orderInfo->boundBottom);
}

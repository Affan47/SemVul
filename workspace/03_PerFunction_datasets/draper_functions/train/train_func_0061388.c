read_length(STREAM *stream)
{
	union
	{
		unsigned char _data[4];
		short _short;
		int _int;
	}
	buffer;

	int len = 0;

	STREAM_read(stream, buffer._data, 1);

	switch (buffer._data[0] >> 6)
	{
		case 0:
		case 1:
			len = buffer._data[0];
			break;

		case 2:
			STREAM_read(stream, &buffer._data[1], 1);
			buffer._data[0] &= 0x3F;

			if (!EXEC_big_endian)
				SWAP_short(&buffer._short);

			len = buffer._short;
			break;

		case 3:
			STREAM_read(stream, &buffer._data[1], 3);
			buffer._data[0] &= 0x3F;

			if (!EXEC_big_endian)
				SWAP_int(&buffer._int);

			len = buffer._int;
			break;
	}

	return len;
}

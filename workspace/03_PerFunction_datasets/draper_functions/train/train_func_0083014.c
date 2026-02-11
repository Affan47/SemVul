tools_file_size_to_crc_size(const infinint & size)
    {
	const infinint ratio = tools_get_extended_size("1G",1024);
	infinint r;
	infinint crc_size;

	if(size != 0)
	{
	    euclide(size, ratio, crc_size, r);
	    if(r > 0)
		++crc_size;
	    crc_size *= 4;
	}
	else
	    crc_size = 1;

	return crc_size;
    }

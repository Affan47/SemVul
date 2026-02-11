put_tiff_header(int fd, int byte_order, int version, int ifd_offset)
{
	uint16 s[2];
	uint32 l;

	lseek(fd, 0, L_SET);

	s[0] = (uint16)(byte_order&0xffff);
	s[1] = (uint16)(version&0xffff);
	if (!write_msb_uint16(fd,s[0]) || !write_msb_uint16(fd,s[1]))
	    return(0);

	l = ifd_offset;
	if (l > 0)
	    if (!write_msb_uint32(fd,l))
		return(0);

	return(1);
}

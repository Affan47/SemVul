is_rar_archive(int fd)
{
	mark_header_t mark;
	const mark_header_t rar_hdr[2] = {{{0x52, 0x61, 0x72, 0x21, 0x1a, 0x07, 0x00}}, {{'U', 'n', 'i', 'q', 'u', 'E', '!'}}};


    if(read(fd, &mark, SIZEOF_MARKHEAD) != SIZEOF_MARKHEAD)
	return FALSE;

    if(memcmp(&mark, &rar_hdr[0], SIZEOF_MARKHEAD) == 0)
	return TRUE;

    if(memcmp(&mark, &rar_hdr[1], SIZEOF_MARKHEAD) == 0)
	return TRUE;

    unrar_dbgmsg("UNRAR: Not a RAR archive\n");
    return FALSE;
}

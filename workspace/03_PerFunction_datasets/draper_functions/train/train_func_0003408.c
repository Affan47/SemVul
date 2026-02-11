start_filesfrom_forwarding(int fd)
{
	if (protocol_version < 31 && OUT_MULTIPLEXED) {


		iobuf.msg.pos = iobuf.msg.len = 0;
		ff_reenable_multiplex = io_end_multiplex_out(MPLX_TO_BUFFERED);
	}
	ff_forward_fd = fd;

	alloc_xbuf(&ff_xb, FILESFROM_BUFLEN);
}

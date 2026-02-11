print_remote_header(mpg123_handle *mh)
{
	struct mpg123_frameinfo i;
	mpg123_info(mh, &i);
	if(i.mode >= 4 || i.mode < 0) i.mode = 4;
	if(i.version >= 3 || i.version < 0) i.version = 3;
	generic_sendmsg("S %s %d %ld %s %d %d %d %d %d %d %d %d %d",
		versions[i.version],
		i.layer,
		i.rate,
		modes[i.mode],
		i.mode_ext,
		i.framesize,
		i.mode == MPG123_M_MONO ? 1 : 2,
		i.flags & MPG123_COPYRIGHT ? 1 : 0,
		i.flags & MPG123_CRC ? 1 : 0,
		i.emphasis,
		i.bitrate,
		i.flags & MPG123_PRIVATE ? 1 : 0,
		i.vbr);
}

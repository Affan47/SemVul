pfs_poll_string( int flags )
{
	static char str[4];
	if(flags&PFS_POLL_READ) {
		str[0] = 'r';
	} else {
		str[0] = '-';
	}
	if(flags&PFS_POLL_WRITE) {
		str[1] = 'w';
	} else {
		str[1] = '-';
	}
	if(flags&PFS_POLL_EXCEPT) {
		str[2] = 'e';
	} else {
		str[2] = '-';
	}
	str[3] = 0;
	return str;
}

search_dup2( int fd, int search )
{
	int i;

	if( (fd<0) || (fd>=pointer_count) || (pointers[fd]==0) || (search<0) || (search>=pointer_count) ) {
		errno = EBADF;
		return -1;
	}

	for( i=search; i<pointer_count; i++ )
		if(!pointers[i]) break;

	if( i==pointer_count ) {
		errno = EMFILE;
		return -1;
	} else {
		return dup2(fd,i);
	}
}

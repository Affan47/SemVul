flock( int fd, int op )
{
	int result = -1;

	if( (fd<0) || (fd>=pointer_count) || (pointers[fd]==0) ) {
		errno = EBADF;
		result = -1;
	} else {
       		result = pointers[fd]->file->flock(op);
	}


	return result;
}

get_full_name( int fd, char *name )
{
	if( (fd<0) || (fd>=pointer_count) || (pointers[fd]==0) ) {
		errno = EBADF;
		return -1;
	}

	strcpy(name,pointers[fd]->file->get_name()->path);
	return 0;
}

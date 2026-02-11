fgetxattr (int fd, const char *name, void *value, size_t size)
{
	int result;

	if( (fd<0) || (fd>=pointer_count) || (pointers[fd]==0) ) {
		errno = EBADF;
		result = -1;
	} else {
		result = pointers[fd]->file->fgetxattr(name,value,size);
	}

	return result;
}

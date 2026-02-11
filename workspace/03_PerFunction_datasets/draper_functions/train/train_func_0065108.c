do_munmap(char *start, unsigned int size, unsigned int mode){
	if (S_ISLNK(mode))
		free(start);
	else
		munmap(start, size);
}

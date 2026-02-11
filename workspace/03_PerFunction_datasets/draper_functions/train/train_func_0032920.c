parrot_opensearch( const char *path, const char *pattern, int flags)
{
	int err;
	size_t buffer_size = 16384;
	char *buffer;

	do {
		buffer = malloc(buffer_size);

		if (buffer==NULL) {
			errno = ENOMEM;
			return NULL;
		}

		#ifdef CCTOOLS_CPU_I386
			err = syscall(SYSCALL32_search,path,pattern,flags,buffer,buffer_size,"parrot_opensearch");
		#else
			err = syscall(SYSCALL64_search,path,pattern,flags,buffer,buffer_size,"parrot_opensearch");
		#endif

		buffer_size*=2;
	} while (err==-1 && errno==ERANGE);

	if (err==-1) return NULL;
        if (err==0) *buffer = '\0';

	SEARCH *result = malloc(sizeof(SEARCH));
	result->entry = (struct searchent*) malloc(sizeof(struct searchent));
	result->entry->info = NULL;
	result->entry->path = NULL;
	result->data = buffer;
	result->i = 0;

	return result;
}

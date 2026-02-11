arg_split_chars(char **argv, char *buffer, int max_args, char *split)
{
	char *ptr = buffer;
	int argc = 0;
	TRACE("going to split '%s', max %d buffer\n", buffer, max_args);


	if(!buffer) return 0;

	while(1) {

		while(strchr(split, *ptr) != NULL && *ptr != 0) *ptr++=0;

		if(*ptr == 0) return argc;


		argv[argc] = ptr;

		TRACE("found arg start= [%s]\n", ptr);


		if(max_args > 0 && argc == max_args-1) {
			char *end_ptr = &ptr[strlen(ptr)-1];
			if(*ptr=='"' && *end_ptr=='"') {
				*argv[argc]++ = 0;
				*end_ptr = 0;
			}
			break;
		}


		if(*ptr == '"') {
			*argv[argc]++ = 0;
			ptr = strchr(ptr+1, '"');
			*ptr++=0;
		} else {

			ptr = strpbrk(ptr, split);
			if(!ptr) break;
		}
		argc++;
	}

	argc++;
	return argc;
}

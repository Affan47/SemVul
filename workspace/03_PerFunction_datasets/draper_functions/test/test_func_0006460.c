proc_currentidentifier(void) {

	char *buffer;

	if(current_function_n == NULL) {
		if((buffer = (char *)malloc(strlen("global") + 1)) == NULL) {
			perror("handle_open_bracket/malloc()");
			exit(-1);
		}
		strcat(buffer, "global");
		current_function_n = buffer;
	}

	if(current_function_t == NULL) {
		if((buffer = (char *)malloc(strlen("extern") + 1)) == NULL) {
			perror("handle_open_bracket/malloc()");
			exit(-1);
		}
		strcat(buffer, "extern");
		current_function_t = buffer;
	}

	if(current_identifier == NULL) {
#ifdef DEBUG
		printf("DEBUG:  caught %s in %s %s()\n",
				current_datatype, current_function_t,
				current_function_n);
#endif
		current_datatype = NULL;
	}
	else {
		proc_data(line_count, current_datatype, pointer_to_datatype,
				current_identifier, current_function_t,
				current_function_n);
#ifdef VDEBUG
		printf("%d %s%s %s in %s %s()\n", line_count,
				current_datatype,
				((pointer_to_datatype) ? "*" : ""),
				current_identifier, current_function_t,
				current_function_n);
#endif
		if( (stor_count % (MEMINCR - 2))  == 0 ) {
	                if ( (userdef = (char **)realloc((void *)userdef,
			(user_count + MEMINCR) * sizeof(char *))) == NULL) {
				perror("proc_currenttype/realloc()");
				exit(-1);
			}
		}
		storage[stor_count++] = current_identifier;
		current_identifier = NULL;
		pointer_to_datatype = 0;
	}
	return;
}

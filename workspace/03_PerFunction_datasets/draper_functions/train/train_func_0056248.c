handle_reserved(const char *str) {

	int i = strlen(str);
	int id;
	char *buffer;

	id = reserved_loopup(str);

	decleration_state = 1;

	if(id == 15 ) {
		typedef_target = 1;
		return;
	};

	if(current_datatype == NULL) {
		if((buffer = (char *)malloc((unsigned)i+1)) == NULL) {
			perror("handle_reserved/malloc()");
			exit(-1);
		}
		strcpy(buffer, str);
	}
	else {
		buffer = current_datatype;
		if((buffer = (char *)realloc(buffer, strlen(buffer) + i + 3))
				== NULL) {
			perror("handle_reserved/realloc()");
			exit(-1);
		}
		strcat(buffer, space);
		strcat(buffer, str);
	}

	if( (id == 14) || (id == 5) ) {
		need_structclosure = 1;
	}
	current_datatype = buffer;
}

read_input_line(int force, int* error)
{
    int ret;
    do {
	if (input_buflen >= input_bufsize) {
	    input_bufsize = input_buflen + 512;
	    input_buf = sresize(input_buf, input_bufsize, char);
	}
	ret = read(0, input_buf+input_buflen, 1);
	if (ret < 0) {
	    perror("read");
	    *error = 1;
	    clear_input_buffers(1);
	    return NULL;
	}
	if (ret == 0) {

	    *error = 1;
	    clear_input_buffers(1);
	    return NULL;
	}

	if (input_buf[input_buflen++] == '\n') {

	    char* buf = input_buf;
	    clear_input_buffers(0);
	    return buf;
	}
    } while(force);

    return NULL;
}

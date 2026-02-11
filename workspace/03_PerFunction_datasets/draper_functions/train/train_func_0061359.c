guess_content_length(char* buf) {
	char* ptr;
	if((ptr=strstr(buf, "Content-Length:")))
		goto found;
	if((ptr=strstr(buf, "content-length:")))
		goto found;
	if((ptr=strstr(buf, "Content-length:")))
		goto found;
	if((ptr=strstr(buf, "CONTENT-LENGTH:")))
		goto found;
	return 0;
found:
	char *error_pos;
	size_t result=(size_t)strtol(ptr+15, &error_pos, 0);

	const size_t reasonable_initial_max=0x400*0x400*10 ;
	if(result>reasonable_initial_max)
		return reasonable_initial_max;
	return 0;
}

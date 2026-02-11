file_input(char* buf, size_t max) {
	size_t read_cnt;

	read_cnt = fread(buf,1,max,DiamDictin);

	if ( read_cnt == max ) {
		return max;
	} else if (read_cnt > 0) {
		return read_cnt;
	} else {
		return YY_NULL;
	}
}

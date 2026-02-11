font_preload(char *s) {
	int k = 0;
	char *buf = strtok(s,",");
	while( buf != NULL ) {
		if(k<64)
			x_preload(buf, k++);
		buf = strtok(NULL,",");
	}
}

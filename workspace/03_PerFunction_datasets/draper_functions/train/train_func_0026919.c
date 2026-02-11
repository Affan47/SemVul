un_unsynch(unsigned char * buf, int len) {

	int i;
	for (i = 0; i < len-1; i++) {
		if ((buf[i] == 0xff) && (buf[i+1] == 0x00)) {
			memmove(buf+i+1, buf+i+2, len-i-2);
			--len;
		}
	}
	return len;
}

swap_buffer(char *buf, size_t len)
{
	unsigned int i;
	for (i=0; i<len; i+=2) {
		char temp = buf[i];
		buf[i] = buf[i+1];
		buf[i+1] = temp;
	}
}

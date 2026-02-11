crc(const uint32_t prev, unsigned char *val, const uint32_t n) {
	uint32_t ret=prev, i;
	uint16_t s1, s2;
	unsigned char *s=val;

	if (ret==0) ret=1;

	s1=ret&0xffff;
	s2=(ret>>16)&0xffff;
	for (i=0; i<n; i++) {
		s1 = (s1 + *s) % 65521;
		s2 = (s1 + s2) % 65521;
		s++;
	}
	ret=(s2<<16)|s1;
	return(ret);
}

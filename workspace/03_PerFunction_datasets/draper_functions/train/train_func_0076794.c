display_size(unsigned v)
{
	if (v > 1024*1024) {
		printf("%8.1f Gbytes", v/((double)(1024*1024)));
	} else if (v > 1024) {
		printf("%8.1f Mbytes", v/((double)(1024)));
	} else {
		printf("%8u Kbytes", v);
	}
}

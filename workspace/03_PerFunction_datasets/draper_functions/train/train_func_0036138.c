print_features (__u16 supported, __u16 enabled, const char *names[])
{
	int i;
	for (i = 0; i < 16; ++i) {
		__u16 mask = 1 << i;
		if ((supported & mask) && names[15 - i])
			printf("\t   %c\t%s\n", (enabled & mask) ? '*' : ' ', names[15 - i]);
	}
}

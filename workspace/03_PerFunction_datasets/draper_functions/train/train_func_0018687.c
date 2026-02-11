print_cap_bitmap(char *val)
{
#define MASK(x) (1U << (x))
	unsigned long long temp;
	__u32 caps[2];
	int i, found=0;

	errno = 0;
	temp = strtoull(val, NULL, 16);
	if (errno) {
		printf("conversion error(%s) ", val);
		return;
	}

	caps[0] = temp & 0xFFFFFFFF;
	caps[1] = (temp & 0xFFFFFFFF) >> 32;
	for (i=0; i< CAP_NAMES; i++) {
		if (MASK(i%32) & caps[i/32]) {
			if (found)
				printf(",");
       			printf("%s", captab[i].name);
			found = 1;
		}
	}
	if (found == 0)
		printf("none");
	printf(" ");
}

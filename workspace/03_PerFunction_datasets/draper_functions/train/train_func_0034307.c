CDB___ham_func3(key, len)
	const void *key;
	u_int32_t len;
{
	const u_int8_t *k;
	u_int32_t n, loop;

	if (len == 0)
		return (0);

#define	HASHC	n = *k++ + 65599 * n
	n = 0;
	k = key;

	loop = (len + 8 - 1) >> 3;
	switch (len & (8 - 1)) {
	case 0:
		do {
			HASHC;
	case 7:
			HASHC;
	case 6:
			HASHC;
	case 5:
			HASHC;
	case 4:
			HASHC;
	case 3:
			HASHC;
	case 2:
			HASHC;
	case 1:
			HASHC;
		} while (--loop);
	}
	return (n);
}

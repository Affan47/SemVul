strnum_cmp(const char *a, const char *b)
{
	char *pa, *pb;
	pa = (char*)a; pb = (char*)b;
	while (*pa && *pb) {
		if (isdigit(*pa) && isdigit(*pb)) {
			long ai, bi;
			ai = strtol(pa, &pa, 10);
			bi = strtol(pb, &pb, 10);
			if (ai != bi) return ai<bi? -1 : ai>bi? 1 : 0;
		} else {
			if (*pa != *pb) break;
			++pa; ++pb;
		}
	}
	if (*pa == *pb)
		return (pa-a) < (pb-b)? -1 : (pa-a) > (pb-b)? 1 : 0;
	return *pa<*pb? -1 : *pa>*pb? 1 : 0;
}

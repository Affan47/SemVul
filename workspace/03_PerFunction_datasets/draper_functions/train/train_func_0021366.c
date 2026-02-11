Argtype(int k, char *buf)
#endif
{
	if (k < 100) {
		sprintf(buf, "%s variable", ftn_types[k]);
		return buf;
		}
	if (k < 200) {
		k -= 100;
		return ftn_types[k];
		}
	if (k < 300) {
		k -= 200;
		if (k == TYSUBR)
			return ftn_types[TYSUBR];
		sprintf(buf, "%s function", ftn_types[k]);
		return buf;
		}
	if (k < 400)
		return "external argument";
	k -= 400;
	sprintf(buf, "%s argument", ftn_types[k]);
	return buf;
	}

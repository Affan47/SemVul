vep_match(struct vep_state *vep, const char *b, const char *e)
{
	struct vep_match *vm;
	const char *q, *r;
	ssize_t l;

	for (vm = vep->match; vm->match; vm++) {
		r = b;
		for (q = vm->match; *q && r < e; q++, r++)
			if (*q != *r)
				break;
		if (*q != '\0' && r == e) {
			if (b != vep->tag) {
				l = e - b;
				assert(l < sizeof vep->tag);
				memmove(vep->tag, b, l);
				vep->tag_i = l;
			}
			return (NULL);
		}
		if (*q == '\0')
			return (vm);
	}
	return (vm);
}

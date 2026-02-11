fetch_size(const void *t,
				     unsigned long xi1, unsigned long xi2,
				     unsigned long long atime)
{
    if (xi2 - xi1 == 1) {


	const struct trie_file *f = trie_getfile(t, xi1);
	if (f->atime < atime)
	    return f->size;
	else
	    return 0;
    } else {
	return index_query(t, xi2, atime) - index_query(t, xi1, atime);
    }
}

octstr_case_search(const Octstr *haystack, const Octstr *needle, long pos)
{
    long i, j;
    int c1, c2;

    seems_valid(haystack);
    seems_valid(needle);
    gw_assert(pos >= 0);


    if (needle->len == 0)
        return 0;

    for (i = pos; i <= haystack->len - needle->len; ++i) {
	for (j = 0; j < needle->len; ++j) {
	    c1 = toupper(haystack->data[i + j]);
	    c2 = toupper(needle->data[j]);
	    if (c1 != c2)
	    	break;
	}
	if (j == needle->len)
	    return i;
    }

    return -1;
}

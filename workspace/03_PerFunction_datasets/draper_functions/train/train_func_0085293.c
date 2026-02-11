get_ntdum (const int *orig, const int *new)
{
    int i, n = 0;

    for (i=2; i<=new[0]; i++) {
	if (!in_gretl_list(orig, new[i])) {
	    n++;
	}
    }

    return n;
}

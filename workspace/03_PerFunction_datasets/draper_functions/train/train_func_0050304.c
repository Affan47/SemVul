in_gretl_list (const int *list, int k)
{
    int i;

    if (list != NULL) {
	for (i=1; i<=list[0]; i++) {
	    if (list[i] == k) {
		return i;
	    }
	}
    }

    return 0;
}

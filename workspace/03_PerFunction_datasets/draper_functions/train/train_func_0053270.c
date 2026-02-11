gretl_list_separator_position (const int *list)
{
    int i;

    if (list != NULL) {
	for (i=1; i<=list[0]; i++) {
	    if (list[i] == LISTSEP) {
		return i;
	    }
	}
    }

    return 0;
}

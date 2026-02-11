pack_array (array, end)
    char **array;
    int    end;
{
    int i, j;

    for (i = 0; i < end; i++) {
	if (array[i] == NULL) {
	    for (j = i+1; j < end; ++j)
		if (array[j] != NULL)
		    array[i++] = array[j];
	    for (; i < end; ++i)
		array[i] = NULL;
	    break;
	}
    }
}

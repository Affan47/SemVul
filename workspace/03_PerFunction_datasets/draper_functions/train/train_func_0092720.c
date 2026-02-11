insertion_sort_debug(data array[], int len, STAT *stat) {
	int i;
	int j;
	data tmp;
	stat->space++;
	stat->allo++;
	for (i = 1; i < len; i++)
		for (j = i; j>0 && array[j-1] > array[j]; j--) {
			tmp = array[j];
			array[j] = array[j-1];
			array[j-1] = tmp;
			stat->comp++;
			stat->swap++;
		}
}

cocktail_sort_debug(data array[], int len, STAT *stat) {
	int begin = 0;
	int end = len-1;
	int i;
	int new_end = begin;
	int new_begin = end;
	data tmp;
	stat->space++;
	stat->allo++;
	while (begin < end) {
		new_end = begin;
		for (i = begin; i < end; i++) {
			if (array[i] > array[i+1]) {
				tmp = array[i];
				array[i] = array[i+1];
				array[i+1] = tmp;
				new_end = i;
				stat->swap++;
			}
			stat->comp++;
		}
		end = new_end;
		new_begin = end;
		for (i = end-1; i >= begin; i--) {
			if (array[i] > array[i+1]) {
				tmp = array[i];
				array[i] = array[i+1];
				array[i+1] = tmp;
				new_begin = i;
				stat->swap++;
			}
			stat->comp++;
		}
		begin = new_begin;
	}
}

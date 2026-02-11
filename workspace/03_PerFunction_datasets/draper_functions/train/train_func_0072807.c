partition_fast_debug(data array[], int len, int pivot_index, STAT *stat) {
	data pivot_value = array[pivot_index];
	data tmp;
	stat->allo += 2;
	stat->space = 2;
	array[pivot_index] = array[len-1];
	array[len-1] = pivot_value;
	stat->swap++;
	int left = 0;
	int right = len-2;
	while (left < right) {
		while (array[left] < pivot_value && left < right) {
			left++;
			stat->comp++;
			}
		while (array[right] >= pivot_value && left < right) {
			right--;
			stat->comp++;
			}
		if (left < right) {
			tmp = array[left];
			array[left] = array[right];
			array[right] = tmp;
			left++;
			right--;
			stat->swap += 2;
		}
	}
	if (left == right)
		if (array[left] < pivot_value)
			left++;
	array[len-1] = array[left];
	array[left] = pivot_value;
	stat->swap++;
	return left;
}

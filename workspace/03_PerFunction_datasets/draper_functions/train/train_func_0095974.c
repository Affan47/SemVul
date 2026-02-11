almost_sorted_array(data array[], int len, int n, int d) {
	int i, j, k;
	data tmp;
	for (i = 0; i < len; i++)
		array[i] = i;
	for (i = 0; i < n; i++) {
		j = rand() % (len-d);
		k = j + (rand() % d);
		tmp = array[j];
		array[j] = array[k];
		array[k] = tmp;
		}
}

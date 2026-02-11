clean_sort_range(struct range *range, int az)
{
	int i, j, k = az - 1, nr_range = az;

	for (i = 0; i < k; i++) {
		if (range[i].end)
			continue;
		for (j = k; j > i; j--) {
			if (range[j].end) {
				k = j;
				break;
			}
		}
		if (j == i)
			break;
		range[i].start = range[k].start;
		range[i].end   = range[k].end;
		range[k].start = 0;
		range[k].end   = 0;
		k--;
	}

	for (i = 0; i < az; i++) {
		if (!range[i].end) {
			nr_range = i;
			break;
		}
	}


	sort(range, nr_range, sizeof(struct range), cmp_range, NULL);

	return nr_range;
}

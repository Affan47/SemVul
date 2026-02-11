rid_partition(fs_rid_vector **v, int count, int left, int right)
{
    int pivot = (left + right) / 2;
    fs_rid pvals[count];
    for (int i=0; i<count; i++) {
	pvals[i] = v[i]->data[pivot];
    }

    rva_swap(v, count, pivot, right);

    int store = left;

    for (int p = left; p < right; p++) {
	if (rva_data_compare(v, count, p, pvals) <= 0) {
	    rva_swap(v, count, store, p);
	    store++;
	}
    }
    rva_swap(v, count, right, store);

    return store;
}

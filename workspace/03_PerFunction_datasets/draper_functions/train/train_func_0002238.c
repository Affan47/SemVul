insertionSort(const uchar** arr, size_t n, int lcp, uint *lcps) {
	for(size_t i=0; i<n; ++i) {
		const uchar* cur = arr[i];

		size_t l = lcp;
		size_t j;
		for(j=i; j; --j) {
			size_t pl = l;
			if (lcps[j]<pl || !lcpCmp(cur, arr[j-1], &l)) {

				if (lcps[j]>=pl) lcps[j] = l;
				l=pl;
				assert(!cmp(cur, arr[j-1]));
				break;
			}

			assert(cmp(cur, arr[j-1]));
			arr[j] = arr[j-1];
			lcps[j+1] = lcps[j];
		}

		assert(j==i || cmp(cur, arr[j+1]));
		assert(j==0 || !cmp(cur, arr[j-1]));
		arr[j] = cur;
		lcps[j+1] = l;
	}
}

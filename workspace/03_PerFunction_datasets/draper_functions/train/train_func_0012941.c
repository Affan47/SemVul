gen_rand_array_c1o2(dsfmt_t *dsfmt, w128_t *array,
				       int size) {
    int i, j;
    w128_t lung;

    lung = dsfmt->status[DSFMT_N];
    do_recursion(&array[0], &dsfmt->status[0], &dsfmt->status[DSFMT_POS1],
		 &lung);
    for (i = 1; i < DSFMT_N - DSFMT_POS1; i++) {
	do_recursion(&array[i], &dsfmt->status[i],
		     &dsfmt->status[i + DSFMT_POS1], &lung);
    }
    for (; i < DSFMT_N; i++) {
	do_recursion(&array[i], &dsfmt->status[i],
		     &array[i + DSFMT_POS1 - DSFMT_N], &lung);
    }
    for (; i < size - DSFMT_N; i++) {
	do_recursion(&array[i], &array[i - DSFMT_N],
		     &array[i + DSFMT_POS1 - DSFMT_N], &lung);
    }
    for (j = 0; j < 2 * DSFMT_N - size; j++) {
	dsfmt->status[j] = array[j + size - DSFMT_N];
    }
    for (; i < size; i++, j++) {
	do_recursion(&array[i], &array[i - DSFMT_N],
		     &array[i + DSFMT_POS1 - DSFMT_N], &lung);
	dsfmt->status[j] = array[i];
    }
    dsfmt->status[DSFMT_N] = lung;
}

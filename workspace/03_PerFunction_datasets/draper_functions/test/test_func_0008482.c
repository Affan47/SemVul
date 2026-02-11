shuffle_long(long *array, long elements)


{
	long i, j, temp;
	for (i = elements-1; i > 0; i--) {
		j=rand_long(i);
		temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

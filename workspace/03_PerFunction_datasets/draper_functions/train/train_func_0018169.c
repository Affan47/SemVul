computeHeapsizes(int heapSize) {
	int heapLeft = heapSize;
	int* result = (int*) malloc(GENERATIONS * sizeof(int));
	int i;

	for (i = GENERATIONS - 1; i >= 0; i--) {
		if (i == 0) {
			result[i] = heapLeft;
		} else {
			result[i] = ceil(heapLeft * (1.0 - GENRATIO));
			heapLeft = heapLeft * GENRATIO;
		}
		if (GEN_DEBUG == 1) {
			printf("GENDEBUG: G%d: %d\n", i, result[i]);
		}
	}

	if (GEN_DEBUG == 1) {
		int sum = 0;
		for (i = 0; i < GENERATIONS; i++) {
			sum = sum + result[i];
		}
		printf("GENDEBUG: Sum of Generations: %d\n", sum);
	}

	return result;
}

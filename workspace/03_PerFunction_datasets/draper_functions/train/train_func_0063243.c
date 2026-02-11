writeCountVector(FILE* fo) {
	for (int i = 0; i < M; i++) {
		fprintf(fo, "%d ", counts[i]);
	}
	fprintf(fo, "%d\n", counts[M]);
}

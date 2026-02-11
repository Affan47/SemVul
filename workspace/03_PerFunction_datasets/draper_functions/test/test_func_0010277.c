mat4_create(int ncolumns) {
	Mat4 *result;

	if (ncolumns < 0) {
		printf("Error in mat4_create().  ncolumns must be >= 0\n");
		return NULL;
	}

	result = calloc(1,sizeof(Mat4));
	if (ncolumns == 0)
		return result;

	if ((result->cells = calloc(ncolumns*4,sizeof(double))) == NULL) {
		printf("Error in mat4_create(): calloc failed on ncolumns == %d\n", ncolumns);
		return NULL;
	}

	result->cols = ncolumns;
	return result;
}

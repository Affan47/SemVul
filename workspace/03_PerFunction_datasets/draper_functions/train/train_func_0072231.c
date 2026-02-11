mult_sparse_dense_mat_transpose(vtx_data * A, double **B, int dim1,
				int dim2, float ***CC)
{


    float *storage;
    int i, j, k;
    double sum;
    float *ewgts;
    int *edges;
    int nedges;
    float **C = *CC;
    if (C != NULL) {
	storage = (float *) realloc(C[0], dim1 * dim2 * sizeof(A[0]));
	*CC = C = (float **) realloc(C, dim1 * sizeof(A));
    } else {
	storage = (float *) malloc(dim1 * dim2 * sizeof(A[0]));
	*CC = C = (float **) malloc(dim1 * sizeof(A));
    }

    for (i = 0; i < dim1; i++) {
	C[i] = storage;
	storage += dim2;
    }

    for (i = 0; i < dim1; i++) {
	edges = A[i].edges;
	ewgts = A[i].ewgts;
	nedges = A[i].nedges;
	for (j = 0; j < dim2; j++) {
	    sum = 0;
	    for (k = 0; k < nedges; k++) {
		sum += ewgts[k] * B[j][edges[k]];
	    }
	    C[i][j] = (float) (sum);
	}
    }
}

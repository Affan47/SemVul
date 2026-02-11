makeTwistedTorus(int dim1, int dim2, int t1, int t2, edgefn ef)
{
    int i, j, li, lj;

    for (i = 0; i < dim1; i++) {
	for (j = 0; j < dim2; j++) {
	    li = (i + t1) % dim1;
	    lj = (j + 1) % dim2;
	    ef (i+j*dim1+1, li+lj*dim1+1);

	    li = (i + 1) % dim1;
	    lj = (j + t2) % dim2;
	    ef(i+j*dim1+1, li+lj*dim1+1);
	}
    }
}

f9_entropy(float **P, int Ng)


{
    int i, j;
    float entropy = 0;

    for (i = 0; i < Ng; ++i)
	for (j = 0; j < Ng; ++j)
	    entropy += P[i][j] * log10(P[i][j] + EPSILON);

    return -entropy;
}

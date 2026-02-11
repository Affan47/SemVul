f3_corr(float **P, int Ng)


{
    int i, j;
    float sum_sqrx = 0, sum_sqry = 0, tmp, *px;
    float meanx = 0, meany = 0, stddevx, stddevy;

    px = vector(0, Ng);
    for (i = 0; i < Ng; ++i)
	px[i] = 0;


    for (i = 0; i < Ng; ++i)
	for (j = 0; j < Ng; ++j)
	    px[i] += P[i][j];


    for (i = 0; i < Ng; ++i) {
	meanx += px[i] * i;
	sum_sqrx += px[i] * i * i;
    }
    meany = meanx;
    sum_sqry = sum_sqrx;
    stddevx = sqrt(sum_sqrx - (meanx * meanx));
    stddevy = stddevx;


    for (tmp = 0, i = 0; i < Ng; ++i)
	for (j = 0; j < Ng; ++j)
	    tmp += i * j * P[i][j];

    G_free(px);

    return (tmp - meanx * meany) / (stddevx * stddevy);


}

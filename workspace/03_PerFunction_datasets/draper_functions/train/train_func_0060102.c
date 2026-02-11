convert_matrix(float *a, int nrl, int nrh, int ncl, int nch)
{
    int i, j, nrow = nrh - nrl + 1, ncol = nch - ncl + 1;
    float **m;


    m = (float **)G_malloc(((nrow + NR_END) * sizeof(float *)));
    m += NR_END;
    m -= nrl;


    m[nrl] = a - ncl;
    for (i = 1, j = nrl + 1; i < nrow; i++, j++)
	m[j] = m[j - 1] + ncol;


    return m;
}

matrix_sortEig_float (float* A,float* d,size_t n)
{
    size_t i;
    struct struct_sort_float * sSort = (struct struct_sort_float *)malloc(n*sizeof(struct struct_sort_float));
    float * Atemp = (float *)malloc(n*n*sizeof(float));

    memcpy(Atemp, A, n*n*sizeof(float));

    for(i = 0 ; i < n ; i++)
    {
        sSort[i].i = i;
        sSort[i].val = d[i];
    }

    qsort(sSort, n, sizeof(struct struct_sort_float), compare_sort_float);

    for(i = 0 ; i < n ; i++)
    {
        d[i] = sSort[i].val;
        memcpy(&A[n*i], &Atemp[n*sSort[i].i], n*sizeof(float));
    }

    free(Atemp);
    free(sSort);
}

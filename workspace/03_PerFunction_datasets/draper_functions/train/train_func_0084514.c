copy_int_vector(int *vec, int n)
{
    int i;
    int *p = alloc_int_vector(n);

    for (i = 0; i < n; i++)
        p[i] = vec[i];

    return p;
}

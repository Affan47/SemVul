count_ones(NUMA  *na, l_int32 nexp, l_int32 index, const char *name)
{
l_int32  i, n, val, sum;

    n = numaGetCount(na);
    sum = 0;
    for (i = 0; i < n; i++) {
        numaGetIValue(na, i, &val);
        if (val == 1) sum++;
    }
    if (!name) return sum;
    if (nexp == sum)
        fprintf(stderr, "Correct: %s[%d]: num. ones: %d\n", name, index, sum);
    else
        fprintf(stderr, "WRONG!: %s[%d]: num. ones: %d\n", name, index, sum);
    return 0;
}

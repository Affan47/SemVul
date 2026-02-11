marshal_test_ref_bool(int i, char *b1, short *b2, int *b3)
{
    int res = 1;
    if (*b1 != 0 && *b1 != 1)
        return 1;
    if (*b2 != 0 && *b2 != -1)
        return 1;
    if (*b3 != 0 && *b3 != 1)
        return 1;
    if (i == ((*b1 << 2) | (-*b2 << 1) | *b3))
        res = 0;
    *b1 = !*b1;
    *b2 = ~*b2;
    *b3 = !*b3;
    return res;
}

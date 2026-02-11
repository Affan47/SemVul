ceil_index (int* a, int l, int r, int key)
{
    while (r - l > 1)
    {
        int m = l + (r - l) / 2;
        if (a[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

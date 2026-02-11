double_comp(const void *xx, const void *yy)
{
    const DCELL *x = xx;
    const DCELL *y = yy;

    if (G_is_d_null_value(x))
	return 0;
    if (*x < *y)
	return -1;
    else if (*x == *y)
	return 0;
    else
	return 1;
}

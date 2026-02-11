cmpforsearch(void *av, void *bv)
{
    Actual_Socket b = (Actual_Socket) bv;
    int as = *(int *)av, bs = b->s;
    if (as < bs)
	return -1;
    if (as > bs)
	return +1;
    return 0;
}

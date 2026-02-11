setSmallMaybe(gap)
    garray_T	*gap;
{
    int		i;
    fold_T	*fp;

    fp = (fold_T *)gap->ga_data;
    for (i = 0; i < gap->ga_len; ++i)
	fp[i].fd_small = MAYBE;
}

deleteFoldRecurse(gap)
    garray_T	*gap;
{
    int		i;

    for (i = 0; i < gap->ga_len; ++i)
	deleteFoldRecurse(&(((fold_T *)(gap->ga_data))[i].fd_nested));
    ga_clear(gap);
}

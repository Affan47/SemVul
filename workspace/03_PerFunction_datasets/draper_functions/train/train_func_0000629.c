syn_stack_alloc()
{
    long	len;
    synstate_T	*to, *from;
    synstate_T	*sstp;

    len = syn_buf->b_ml.ml_line_count / SST_DIST + Rows * 2;
    if (len < SST_MIN_ENTRIES)
	len = SST_MIN_ENTRIES;
    else if (len > SST_MAX_ENTRIES)
	len = SST_MAX_ENTRIES;
    if (syn_block->b_sst_len > len * 2 || syn_block->b_sst_len < len)
    {

	len = syn_buf->b_ml.ml_line_count;
	len = (len + len / 2) / SST_DIST + Rows * 2;
	if (len < SST_MIN_ENTRIES)
	    len = SST_MIN_ENTRIES;
	else if (len > SST_MAX_ENTRIES)
	    len = SST_MAX_ENTRIES;

	if (syn_block->b_sst_array != NULL)
	{


	    while (syn_block->b_sst_len - syn_block->b_sst_freecount + 2 > len
		    && syn_stack_cleanup())
		;
	    if (len < syn_block->b_sst_len - syn_block->b_sst_freecount + 2)
		len = syn_block->b_sst_len - syn_block->b_sst_freecount + 2;
	}

	sstp = (synstate_T *)alloc_clear((unsigned)(len * sizeof(synstate_T)));
	if (sstp == NULL)
	    return;

	to = sstp - 1;
	if (syn_block->b_sst_array != NULL)
	{

	    for (from = syn_block->b_sst_first; from != NULL;
							from = from->sst_next)
	    {
		++to;
		*to = *from;
		to->sst_next = to + 1;
	    }
	}
	if (to != sstp - 1)
	{
	    to->sst_next = NULL;
	    syn_block->b_sst_first = sstp;
	    syn_block->b_sst_freecount = len - (int)(to - sstp) - 1;
	}
	else
	{
	    syn_block->b_sst_first = NULL;
	    syn_block->b_sst_freecount = len;
	}


	syn_block->b_sst_firstfree = to + 1;
	while (++to < sstp + len)
	    to->sst_next = to + 1;
	(sstp + len - 1)->sst_next = NULL;

	vim_free(syn_block->b_sst_array);
	syn_block->b_sst_array = sstp;
	syn_block->b_sst_len = len;
    }
}

read_tree_node(fd, byts, idxs, maxidx, startidx, prefixtree, maxprefcondnr)
    FILE	*fd;
    char_u	*byts;
    idx_T	*idxs;
    int		maxidx;
    idx_T	startidx;
    int		prefixtree;
    int		maxprefcondnr;
{
    int		len;
    int		i;
    int		n;
    idx_T	idx = startidx;
    int		c;
    int		c2;
#define SHARED_MASK	0x8000000

    len = getc(fd);
    if (len <= 0)
	return SP_TRUNCERROR;

    if (startidx + len >= maxidx)
	return SP_FORMERROR;
    byts[idx++] = len;


    for (i = 1; i <= len; ++i)
    {
	c = getc(fd);
	if (c < 0)
	    return SP_TRUNCERROR;
	if (c <= BY_SPECIAL)
	{
	    if (c == BY_NOFLAGS && !prefixtree)
	    {

		idxs[idx] = 0;
		c = 0;
	    }
	    else if (c != BY_INDEX)
	    {
		if (prefixtree)
		{


		    if (c == BY_FLAGS)
			c = getc(fd) << 24;
		    else
			c = 0;

		    c |= getc(fd);

		    n = get2c(fd);
		    if (n >= maxprefcondnr)
			return SP_FORMERROR;
		    c |= (n << 8);
		}
		else
		{


		    c2 = c;
		    c = getc(fd);
		    if (c2 == BY_FLAGS2)
			c = (getc(fd) << 8) + c;
		    if (c & WF_REGION)
			c = (getc(fd) << 16) + c;
		    if (c & WF_AFX)
			c = (getc(fd) << 24) + c;
		}

		idxs[idx] = c;
		c = 0;
	    }
	    else
	    {

		n = get3c(fd);
		if (n < 0 || n >= maxidx)
		    return SP_FORMERROR;
		idxs[idx] = n + SHARED_MASK;
		c = getc(fd);
	    }
	}
	byts[idx++] = c;
    }


    for (i = 1; i <= len; ++i)
	if (byts[startidx + i] != 0)
	{
	    if (idxs[startidx + i] & SHARED_MASK)
		idxs[startidx + i] &= ~SHARED_MASK;
	    else
	    {
		idxs[startidx + i] = idx;
		idx = read_tree_node(fd, byts, idxs, maxidx, idx,
						     prefixtree, maxprefcondnr);
		if (idx < 0)
		    break;
	    }
	}

    return idx;
}

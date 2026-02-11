data_tree_permutation(archive_num src, archive_num dst, archive_num x)
    {
	if(src < dst)
	    if(x < src || x > dst)
		return x;
	    else
		if(x == src)
		    return dst;
		else
		    return x-1;
	else
	    if(src == dst)
		return x;
	    else
		if(x > src || x < dst)
		    return x;
		else
		    if(x == src)
			return dst;
		    else
			return x+1;
    }

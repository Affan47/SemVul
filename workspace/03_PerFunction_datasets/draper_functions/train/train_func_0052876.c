nc_blkio_init(size_t bufsize,
	      size_t value_size,
	      int rank,
	      int chunked,
	      nciter_t *iter
    ) {
    int stat = NC_NOERR;
    int i;
    long long prod;
    size_t *dims = iter->dimsizes;

    iter->rank = rank;
    iter->first = 1;
    iter->more = 1;
    iter->chunked = chunked;
    prod = value_size;
    if(iter->chunked == 0) {
	iter->right_dim = rank - 1;
	for(i = rank; i > 0; i--) {
	    if(prod*dims[i-1] <= bufsize) {
		prod *= dims[i-1];
		iter->right_dim--;
	    } else {
		break;
	    }
	}
	if (i > 0) {
	    iter->rows = bufsize/prod;
	    iter->numrows = dims[iter->right_dim] / iter->rows;
	    iter->leftover = dims[iter->right_dim] - iter->numrows * iter->rows;
	    iter->cur = 1;
	    iter->inc = iter->rows;
	    return stat;
	}

	iter->right_dim = 0;
	iter->rows = dims[0];
	iter->inc = 0;
	return stat;
    }

    for(i = 0; i < rank; i++) {
	prod *= iter->chunksizes[i];
    }
    if(prod > bufsize) {
	stat = NC_ENOMEM;
	fprintf(stderr, "chunksize (= %ld) > copy_buffer size (= %ld)\n",
			(long)prod, (long)bufsize);
    }
    return stat;
}

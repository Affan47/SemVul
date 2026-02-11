nc_next_iter(nciter_t *iter,
	     size_t *start,
	     size_t *count
    ) {
    int i;


    if(iter->first) {
	if(!iter->chunked) {
	    for(i = 0; i < iter->right_dim; i++) {
		start[i] = 0;
		count[i] = 1;
	    }
	    start[iter->right_dim] = 0;
	    count[iter->right_dim] = iter->rows;
	    for(i = iter->right_dim + 1; i < iter->rank; i++) {
		start[i] = 0;
		count[i] = iter->dimsizes[i];
	    }
	} else {
#ifdef DOCHUNK
	    for(i = 0; i < iter->rank; i++) {
		start[i] = 0;
		count[i] = iter->chunksizes[i];
	    }
#endif
	}
	iter->first = 0;
    } else {
	if(!iter->chunked) {
	    iter->more = up_start(iter->rank, iter->dimsizes, iter->right_dim,
				  iter->inc, start);

	    if(iter->cur < iter->numrows) {
		iter->inc = iter->rows;
		count[iter->right_dim] = iter->rows;
		iter->cur++;
	    } else {
		if(iter->leftover > 0) {
		    count[iter->right_dim] = iter->leftover;
		    iter->inc = iter->leftover;
		    iter->cur = 0;
		}
	    }
	} else {
#ifdef DOCHUNK
	    iter->more = up_start_by_chunks(iter->rank, iter->dimsizes,
					    iter->chunksizes, start);

	    for(i = 0; i < iter->rank; i++) {
		int leftover = iter->dimsizes[i] - start[i];
		count[i] = iter->chunksizes[i];
		if(leftover < count[i])
		    count[i] = leftover;
	    }
#endif
	}
    }
    iter->to_get = 1;
    for(i = 0; i < iter->rank; i++) {
	iter->to_get *= count[i];
    }
    return iter->more == 0 ? 0 : iter->to_get ;
}

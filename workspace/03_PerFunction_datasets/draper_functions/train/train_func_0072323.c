can_compare_DA_data(const giiDataArray *d1,const giiDataArray *d2,
                               int verb)
{
    int c, top, rv = 1;
    int lverb = verb;

    if( G.verb > lverb ) lverb = G.verb;

    if( !d1 || !d2 ) {
        if(lverb>1) printf("-- comp DAs: have NULL DA(s) (%p, %p)\n",
                           (void*)d1,(void*)d2);
        return 0;
    }

    if( d1->datatype != d2->datatype ) {
        rv = 0;
        if( lverb > 1 )
            printf("-- comp DAs: DA datatype diff: %d (%s) vs. %d (%s)\n",
                   d1->datatype, gifti_datatype2str(d1->datatype),
                   d2->datatype, gifti_datatype2str(d2->datatype));
        if( lverb < 3 ) return 0;
    }

    if( d1->ind_ord != d2->ind_ord ) {
        rv = 0;
        if( lverb > 1 )
            printf("-- comp DAs: ind_ord diff: %d (%s) vs. %d (%s)\n",
               d1->ind_ord,
               gifti_list_index2string(gifti_index_order_list, d1->ind_ord),
               d2->ind_ord,
               gifti_list_index2string(gifti_index_order_list, d2->ind_ord));
        if( lverb < 3 ) return 0;
    }

    if( d1->num_dim != d2->num_dim ) {
        rv = 0;
        if( lverb > 1 ) printf("-- comp DAs: num_dim diff: %d vs. %d\n",
                               d1->num_dim, d2->num_dim );
        if( lverb < 3 ) return 0;
    }


    top = d1->num_dim < d2->num_dim ? d1->num_dim : d2->num_dim;
    for( c = 0; c < top; c++ ) if( d1->dims[c] != d2->dims[c] ) break;
    if( c < top ) {
        rv = 0;
        if( lverb > 1 ) {
            printf("-- comp DAs: DA dims diff (length %d)\n   ", top);
            gifti_disp_raw_data(d1->dims, NIFTI_TYPE_INT32, top, 0, stdout);
            printf("  vs  ");
            gifti_disp_raw_data(d2->dims, NIFTI_TYPE_INT32, top, 1, stdout);
        }
        if( lverb < 3 ) return 0;
    }

    if( d1->nvals != d2->nvals ) {
        rv = 0;
        if( lverb > 1 ) printf("-- comp DAs: nvals diff: %lld vs. %lld\n",
                               d1->nvals, d2->nvals);
        if( lverb < 3 ) return 0;
    }

    if( d1->nbyper != d2->nbyper ) {
        rv = 0;
        if( lverb > 1 ) printf("-- comp DAs: nbyper diff: %d vs. %d\n",
                               d1->nbyper, d2->nbyper);
        if( lverb < 3 ) return 0;
    }


    if( ! gifti_valid_dims(d1, 0) ) {
        rv = 0;
        if( lverb > 1 ) printf("-- comp DAs: dims not valid\n");
    }

    return rv;
}

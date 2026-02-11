gifti_valid_DataArray(const giiDataArray * da, int whine)
{
    int errs = 0, nbyper;

    if( !da ) {
        if( whine || G.verb > 2 ) fprintf(stderr,"** invalid darray pointer\n");
        return 0;
    }

    if( ! gifti_intent_is_valid(da->intent) ) {
        if( whine || G.verb > 3 )
            fprintf(stderr,"** invalid darray intent code = %d\n", da->intent);
        errs++;
    }

    if( ! gifti_valid_datatype(da->datatype, whine) )
        errs++;


    if( da->ind_ord<=GIFTI_IND_ORD_UNDEF || da->ind_ord>GIFTI_IND_ORD_MAX ) {
        if( whine || G.verb > 3 )
            fprintf(stderr,"** invalid darray ind_ord = %d\n", da->ind_ord);
        errs++;
    }

    if( ! gifti_valid_num_dim(da->num_dim, whine) )
        errs++;

    if( ! gifti_valid_dims(da, whine) )
        errs++;

    if( da->encoding<=GIFTI_ENCODING_UNDEF || da->encoding>GIFTI_ENCODING_MAX ){
        if( whine || G.verb > 3 )
            fprintf(stderr,"** invalid darray encoding = %d\n", da->encoding);
        errs++;
    }

    if( da->endian<=GIFTI_ENDIAN_UNDEF || da->endian>GIFTI_ENDIAN_MAX ) {
        if( whine || G.verb > 3 )
            fprintf(stderr,"** invalid darray endian = %d\n", da->endian);
        errs++;
    }


    if( ! gifti_valid_nvpairs(&da->meta, whine) )
        errs++;

    if( da->nvals <= 0 ) {
        if( whine || G.verb > 3 )
            fprintf(stderr,"** invalid darray nvals = %u\n",
                    (unsigned)da->nvals );
        errs++;
    }

    if( ! gifti_valid_nbyper(da->nbyper, whine) ) errs++;
    if( ! gifti_valid_nvpairs(&da->ex_atrs, whine) ) errs++;


    errs += gifti_datatype_sizes(da->datatype, &nbyper, NULL);
    if( gifti_valid_nbyper(nbyper, 0) && nbyper != da->nbyper ) {
        if( whine || G.verb > 3 )
            fprintf(stderr,"** nbyper %d, does not match type %s\n",
                    nbyper, gifti_datatype2str(da->datatype));
        errs++;
    }

    if( errs ) return 0;

    return 1;
}

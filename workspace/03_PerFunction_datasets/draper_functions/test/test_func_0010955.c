gifti_read_dset_numDA(const char * fname)
{
    gifti_image * gim;
    int           numDA;

    if( !fname ) {
        fprintf(stderr,"** NULL to gifti_read_dset_numDA\n");
        return -1;
    }

    if( G.verb > 2 ) fprintf(stderr,"++ read dset numDA, file '%s'\n",fname);

    gim = gifti_read_da_list(fname, 0, NULL, 0);

    if( !gim ) return -1;

    numDA = gim->numDA;

    if(G.verb > 1)
        fprintf(stderr,"++ read dset numDA, file '%s', numDA = %d\n",
                fname, numDA);

    gifti_free_image(gim);

    return numDA;
}

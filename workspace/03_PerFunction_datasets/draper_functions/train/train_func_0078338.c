gifti_clear_DataArray(giiDataArray * da)
{
    if(!da) { fprintf(stderr,"** NULL in clear_DataArray\n"); return 1; }

    if( G.verb > 5 ) fprintf(stderr,"-- clearing DataArray\n");

    memset(da, 0, sizeof(giiDataArray));

    da->ext_fname = NULL;
    gifti_clear_nvpairs(&da->meta);
    da->coordsys = NULL;
    da->data = NULL;
    gifti_clear_nvpairs(&da->ex_atrs);

    return 0;
}

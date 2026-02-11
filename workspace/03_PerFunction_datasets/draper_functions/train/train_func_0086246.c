push_darray(gxml_data * xd, const char ** attr)
{
    giiDataArray * da;


    xd->eleDA++;

    if( xd->da_list ) {
        if( (xd->da_ind < xd->da_len) &&
            (xd->da_list[xd->da_ind] == xd->eleDA-1) )
        {
            if(xd->verb > 1) fprintf(stderr,"++ keeping DA[%d]\n",xd->eleDA-1);
            xd->da_ind++;
        } else {
            if(xd->verb > 1) fprintf(stderr,"++ skipping DA[%d]\n",xd->eleDA-1);
            xd->skip = xd->depth;
            return 1;
        }
    }

    if( gifti_add_empty_darray(xd->gim, 1) ) return 1;

    da = xd->gim->darray[xd->gim->numDA-1];


    if( gifti_set_DA_atrs(da, attr, 0, 1) ) return 1;
    (void)gifti_valid_DataArray(da, xd->verb > 1);


    if( da->nvals>0 && da->nbyper>0 )
        update_xml_buf_size(xd, da->nvals*da->nbyper);

    if( xd->verb > 4 ) gifti_disp_DataArray("push:", da, 0);

    return 0;
}

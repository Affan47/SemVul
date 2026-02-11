match_dim_scale(hid_t did, unsigned dim, hid_t dsid, void *visitor_data)
{
    int       ret = 0;
    hid_t     sid;
    hssize_t  nelmts;
    hsize_t   dims[H5S_MAX_RANK];
    hsize_t   storage_size;


    visitor_data = visitor_data;


    if((sid = H5Dget_space(did)) < 0)
        goto out;


    if(H5Sget_simple_extent_dims(sid,dims,NULL) < 0)
        goto out;


    if(H5Sclose(sid) < 0)
        goto out;


    if((sid = H5Dget_space(dsid)) < 0)
        goto out;


    if((nelmts = H5Sget_simple_extent_npoints(sid)) < 0)
        goto out;


    if(H5Sclose(sid) < 0)
        goto out;


    if(nelmts == (hssize_t)dims[dim])
        ret = 1;


    storage_size=H5Dget_storage_size(dsid);

    if(storage_size==0)
        ret = 0;

    return ret;

out:
    H5E_BEGIN_TRY {
        H5Sclose(sid);
    } H5E_END_TRY;
    return FAIL;
}

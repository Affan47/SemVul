long_desc_cb(unsigned UNUSED n, const H5E_error2_t *err_desc, void *client_data)
{
    char *real_desc  = (char *)client_data;

    if(err_desc->desc != NULL && HDstrcmp(err_desc->desc, real_desc) == 0)
        return(0);
    else
        return(-1);
}

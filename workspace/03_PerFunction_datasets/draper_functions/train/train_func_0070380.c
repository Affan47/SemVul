v1h_put_NC_attr(v1hs *psp, const NC_attr *attrp)
{
        int status;

        status = v1h_put_NC_string(psp, attrp->name);
        if(status != ENOERR)
                return status;

        status = v1h_put_nc_type(psp, &attrp->type);
        if(status != ENOERR)
                return status;

        status = v1h_put_size_t(psp, &attrp->nelems);
        if(status != ENOERR)
                return status;

        status = v1h_put_NC_attrV(psp, attrp);
        if(status != ENOERR)
                return status;

        return ENOERR;
}

NC_computeshapes(NC *ncp)
{
        NC_var **vpp = (NC_var **)ncp->vars.value;
        NC_var *const *const end = &vpp[ncp->vars.nelems];
        NC_var *first_var = NULL;
        NC_var *first_rec = NULL;
        int status;

        ncp->begin_var = (off_t) ncp->xsz;
        ncp->begin_rec = (off_t) ncp->xsz;
        ncp->recsize = 0;

        if(ncp->vars.nelems == 0)
                return(0);

        for( ; vpp < end; vpp++)
        {
                status = NC_var_shape(*vpp, &ncp->dims);
                if(status != ENOERR)
                        return(status);

                if(IS_RECVAR(*vpp))
                {
                        if(first_rec == NULL)
                                first_rec = *vpp;
                        ncp->recsize += (*vpp)->len;
                }
                else
                {
                        if(first_var == NULL)
                                first_var = *vpp;


                        ncp->begin_rec = (*vpp)->begin + (off_t)(*vpp)->len;
                }
        }

        if(first_rec != NULL)
        {
                assert(ncp->begin_rec <= first_rec->begin);
                ncp->begin_rec = first_rec->begin;


                if(ncp->recsize == first_rec->len)
                        ncp->recsize = *first_rec->dsizes * first_rec->xsz;
        }

        if(first_var != NULL)
        {
                ncp->begin_var = first_var->begin;
        }
        else
        {
                ncp->begin_var = ncp->begin_rec;
        }

        assert(ncp->begin_var > 0);
        assert(ncp->xsz <= (size_t)ncp->begin_var);
        assert(ncp->begin_rec > 0);
        assert(ncp->begin_var <= ncp->begin_rec);

        return(ENOERR);
}

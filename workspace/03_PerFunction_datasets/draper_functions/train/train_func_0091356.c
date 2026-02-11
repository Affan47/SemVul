PerlIOAPR_dup(pTHX_ PerlIO *f, PerlIO *o,
                             CLONE_PARAMS *param, int flags)
{
    apr_status_t rc;

    if ((f = PerlIOBase_dup(aTHX_ f, o, param, flags))) {
        PerlIOAPR *fst = PerlIOSelf(f, PerlIOAPR);
        PerlIOAPR *ost = PerlIOSelf(o, PerlIOAPR);

        rc = apr_file_dup(&fst->file, ost->file, ost->pool);

        MP_TRACE_o(MP_FUNC, "obj=0x%lx, "
                   "file=0x%lx => 0x%lx, rc=%d",
                   (unsigned long)f, (unsigned long)ost->file,
                   (unsigned long)fst->file, rc);

        if (rc == APR_SUCCESS) {
            fst->pool = ost->pool;
            return f;
        }
    }

    return NULL;
}

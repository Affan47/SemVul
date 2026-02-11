venus_getattr(struct super_block *sb, struct CodaFid *fid,
		     struct coda_vattr *attr)
{
        union inputArgs *inp;
        union outputArgs *outp;
        int insize, outsize, error;

        insize = SIZE(getattr);
	UPARG(CODA_GETATTR);
        inp->coda_getattr.VFid = *fid;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);
	if (!error)
		*attr = outp->coda_getattr.attr;

	CODA_FREE(inp, insize);
        return error;
}

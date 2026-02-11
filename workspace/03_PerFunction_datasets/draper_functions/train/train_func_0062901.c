venus_close(struct super_block *sb, struct CodaFid *fid, int flags,
		kuid_t uid)
{
	union inputArgs *inp;
	union outputArgs *outp;
	int insize, outsize, error;

	insize = SIZE(release);
	UPARG(CODA_CLOSE);

	inp->ih.uid = from_kuid(&init_user_ns, uid);
        inp->coda_close.VFid = *fid;
        inp->coda_close.flags = flags;

	error = coda_upcall(coda_vcp(sb), insize, &outsize, inp);

	CODA_FREE(inp, insize);
        return error;
}

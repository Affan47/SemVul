nfsd_proc_getattr(struct svc_rqst *rqstp, struct nfsd_fhandle  *argp,
					  struct nfsd_attrstat *resp)
{
	__be32 nfserr;
	dprintk("nfsd: GETATTR  %s\n", SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	nfserr = fh_verify(rqstp, &resp->fh, 0,
			NFSD_MAY_NOP | NFSD_MAY_BYPASS_GSS_ON_ROOT);
	return nfsd_return_attrs(nfserr, resp);
}

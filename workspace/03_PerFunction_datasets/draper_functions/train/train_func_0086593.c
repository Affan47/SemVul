nfsd3_proc_setattr(struct svc_rqst *rqstp, struct nfsd3_sattrargs *argp,
					   struct nfsd3_attrstat  *resp)
{
	__be32	nfserr;

	dprintk("nfsd: SETATTR(3)  %s\n",
				SVCFH_fmt(&argp->fh));

	fh_copy(&resp->fh, &argp->fh);
	nfserr = nfsd_setattr(rqstp, &resp->fh, &argp->attrs,
			      argp->check_guard, argp->guardtime);
	RETURN_STATUS(nfserr);
}

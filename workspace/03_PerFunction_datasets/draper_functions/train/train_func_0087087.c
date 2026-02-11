nfsd3_proc_write(struct svc_rqst *rqstp, struct nfsd3_writeargs *argp,
					 struct nfsd3_writeres  *resp)
{
	__be32	nfserr;
	unsigned long cnt = argp->len;

	dprintk("nfsd: WRITE(3)    %s %d bytes at %Lu%s\n",
				SVCFH_fmt(&argp->fh),
				argp->len,
				(unsigned long long) argp->offset,
				argp->stable? " stable" : "");

	fh_copy(&resp->fh, &argp->fh);
	resp->committed = argp->stable;
	nfserr = nfsd_write(rqstp, &resp->fh, NULL,
				   argp->offset,
				   rqstp->rq_vec, argp->vlen,
				   &cnt,
				   &resp->committed);
	resp->count = cnt;
	RETURN_STATUS(nfserr);
}

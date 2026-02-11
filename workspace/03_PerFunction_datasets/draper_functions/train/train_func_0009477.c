nfsd_return_dirop(__be32 err, struct nfsd_diropres *resp)
{
	if (err) return err;
	return fh_getattr(&resp->fh, &resp->stat);
}

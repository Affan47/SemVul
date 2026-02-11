nlm_xdr_dec_testres(struct rpc_rqst *req,
			       struct xdr_stream *xdr,
			       struct nlm_res *result)
{
	int error;

	error = decode_cookie(xdr, &result->cookie);
	if (unlikely(error))
		goto out;
	error = decode_nlm_testrply(xdr, result);
out:
	return error;
}

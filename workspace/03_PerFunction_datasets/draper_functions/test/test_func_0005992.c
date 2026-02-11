rsa_dec(struct akcipher_request *req)
{
	struct crypto_akcipher *tfm = crypto_akcipher_reqtfm(req);
	const struct rsa_key *pkey = rsa_get_key(tfm);
	MPI c, m = mpi_alloc(0);
	int ret = 0;
	int sign;

	if (!m)
		return -ENOMEM;

	if (unlikely(!pkey->n || !pkey->d)) {
		ret = -EINVAL;
		goto err_free_m;
	}

	if (req->dst_len < mpi_get_size(pkey->n)) {
		req->dst_len = mpi_get_size(pkey->n);
		ret = -EOVERFLOW;
		goto err_free_m;
	}

	ret = -ENOMEM;
	c = mpi_read_raw_from_sgl(req->src, req->src_len);
	if (!c)
		goto err_free_m;

	ret = _rsa_dec(pkey, m, c);
	if (ret)
		goto err_free_c;

	ret = mpi_write_to_sgl(m, req->dst, &req->dst_len, &sign);
	if (ret)
		goto err_free_c;

	if (sign < 0)
		ret = -EBADMSG;
err_free_c:
	mpi_free(c);
err_free_m:
	mpi_free(m);
	return ret;
}

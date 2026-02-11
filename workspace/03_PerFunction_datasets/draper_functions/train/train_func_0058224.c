nfs4_make_rec_clidname(char *dname, const struct xdr_netobj *clname)
{
	struct xdr_netobj cksum;
	struct hash_desc desc;
	struct scatterlist sg;
	int status;

	dprintk("NFSD: nfs4_make_rec_clidname for %.*s\n",
			clname->len, clname->data);
	desc.flags = CRYPTO_TFM_REQ_MAY_SLEEP;
	desc.tfm = crypto_alloc_hash("md5", 0, CRYPTO_ALG_ASYNC);
	if (IS_ERR(desc.tfm)) {
		status = PTR_ERR(desc.tfm);
		goto out_no_tfm;
	}

	cksum.len = crypto_hash_digestsize(desc.tfm);
	cksum.data = kmalloc(cksum.len, GFP_KERNEL);
	if (cksum.data == NULL) {
		status = -ENOMEM;
 		goto out;
	}

	sg_init_one(&sg, clname->data, clname->len);

	status = crypto_hash_digest(&desc, &sg, sg.length, cksum.data);
	if (status)
		goto out;

	md5_to_hex(dname, cksum.data);

	status = 0;
out:
	kfree(cksum.data);
	crypto_free_hash(desc.tfm);
out_no_tfm:
	return status;
}

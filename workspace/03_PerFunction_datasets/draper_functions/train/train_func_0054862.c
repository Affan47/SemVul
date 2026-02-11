mgt_get_request(islpci_private *priv, enum oid_num_t n, int extra, void *data,
		union oid_res_t *res)
{

	int ret = -EIO;
	int reslen = 0;
	struct islpci_mgmtframe *response = NULL;

	int dlen;
	void *cache, *_res = NULL;
	u32 oid;

	BUG_ON(OID_NUM_LAST <= n);
	BUG_ON(extra > isl_oid[n].range);

	res->ptr = NULL;

	if (!priv->mib)

		return -1;

	dlen = isl_oid[n].size;
	cache = priv->mib[n];
	cache += cache ? extra * dlen : 0;
	oid = isl_oid[n].oid + extra;
	reslen = dlen;

	if (cache)
		down_read(&priv->mib_sem);

	if (islpci_get_state(priv) >= PRV_STATE_READY) {
		ret = islpci_mgt_transaction(priv->ndev, PIMFOR_OP_GET,
					     oid, data, dlen, &response);
		if (ret || !response ||
		    response->header->operation == PIMFOR_OP_ERROR) {
			if (response)
				islpci_mgt_release(response);
			ret = -EIO;
		}
		if (!ret) {
			_res = response->data;
			reslen = response->header->length;
		}
	} else if (cache) {
		_res = cache;
		ret = 0;
	}
	if ((isl_oid[n].flags & OID_FLAG_TYPE) == OID_TYPE_U32)
		res->u = ret ? 0 : le32_to_cpu(*(u32 *) _res);
	else {
		res->ptr = kmalloc(reslen, GFP_KERNEL);
		BUG_ON(res->ptr == NULL);
		if (ret)
			memset(res->ptr, 0, reslen);
		else {
			memcpy(res->ptr, _res, reslen);
			mgt_le_to_cpu(isl_oid[n].flags & OID_FLAG_TYPE,
				      res->ptr);
		}
	}
	if (cache)
		up_read(&priv->mib_sem);

	if (response && !ret)
		islpci_mgt_release(response);

	if (reslen > isl_oid[n].size)
		printk(KERN_DEBUG
		       "mgt_get_request(0x%x): received data length was bigger "
		       "than expected (%d > %d). Memory is probably corrupted...",
		       oid, reslen, isl_oid[n].size);

	return ret;
}

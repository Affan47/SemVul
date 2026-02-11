mgt_set(islpci_private *priv, enum oid_num_t n, void *data)
{
	BUG_ON(OID_NUM_LAST <= n);
	BUG_ON(priv->mib[n] == NULL);

	memcpy(priv->mib[n], data, isl_oid[n].size);
	mgt_cpu_to_le(isl_oid[n].flags & OID_FLAG_TYPE, priv->mib[n]);
}

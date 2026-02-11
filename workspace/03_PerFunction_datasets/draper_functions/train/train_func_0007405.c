sasl_map_new_private()
{
	Slapi_RWLock *new_lock =  slapi_new_rwlock();
	sasl_map_private *new_priv = NULL;
	if (NULL == new_lock) {
		return NULL;
	}
	new_priv = (sasl_map_private *)slapi_ch_calloc(1,sizeof(sasl_map_private));
	new_priv->lock = new_lock;
	return new_priv;
}

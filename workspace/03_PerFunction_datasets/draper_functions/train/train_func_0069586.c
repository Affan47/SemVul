ruv_destroy (RUV **ruv)
{
	if (ruv != NULL && *ruv != NULL)
	{
		if ((*ruv)->elements)
		{
			dl_cleanup ((*ruv)->elements, ruvFreeReplica);
			dl_free (&(*ruv)->elements);
		}

		slapi_ch_free ((void **)&((*ruv)->replGen));

		if ((*ruv)->lock)
		{
			slapi_destroy_rwlock ((*ruv)->lock);
		}

		slapi_ch_free ((void**)ruv);
	}
}

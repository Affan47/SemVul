examine_update_vector(Private_Repl_Protocol *prp, RUV *remote_ruv)
{
	int return_value;

	PR_ASSERT(NULL != prp);
	if (NULL == prp)
	{
		return_value = EXAMINE_RUV_PARAM_ERROR;
	}
	else if (NULL == remote_ruv)
	{
		return_value = EXAMINE_RUV_PRISTINE_REPLICA;
	}
	else
	{
		char *local_gen = NULL;
		char *remote_gen = ruv_get_replica_generation(remote_ruv);
		Object *local_ruv_obj;
		RUV *local_ruv;
		Replica *replica;

		PR_ASSERT(NULL != prp->replica_object);
		replica = object_get_data(prp->replica_object);
		PR_ASSERT(NULL != replica);
		local_ruv_obj = replica_get_ruv (replica);
		if (NULL != local_ruv_obj)
		{
			local_ruv = (RUV*)object_get_data (local_ruv_obj);
			PR_ASSERT (local_ruv);
			local_gen = ruv_get_replica_generation(local_ruv);
			object_release (local_ruv_obj);
		}
		if (NULL == remote_gen || NULL == local_gen || strcmp(remote_gen, local_gen) != 0)
		{
			return_value = EXAMINE_RUV_GENERATION_MISMATCH;
		}
		else
		{
			return_value = EXAMINE_RUV_OK;
		}
		slapi_ch_free((void**)&remote_gen);
		slapi_ch_free((void**)&local_gen);
	}
	return return_value;
}

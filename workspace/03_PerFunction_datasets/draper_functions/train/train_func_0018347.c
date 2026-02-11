_credential_replayed(slurm_cred_ctx_t ctx, slurm_cred_t *cred)
{
	ListIterator  i = NULL;
	cred_state_t *s = NULL;

	_clear_expired_credential_states(ctx);

	i = list_iterator_create(ctx->state_list);

	while ((s = list_next(i))) {
		if ((s->jobid  == cred->jobid)  &&
		    (s->stepid == cred->stepid) &&
		    (s->ctime  == cred->ctime))
			break;
	}

	list_iterator_destroy(i);


	if (s)
		return true;


	_insert_cred_state(ctx, cred);
	return false;
}

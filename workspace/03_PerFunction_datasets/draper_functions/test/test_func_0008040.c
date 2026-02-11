_csngen_call_callbacks (const CSNGen *gen, const CSN *csn, PRBool abort)
{
	int cookie;
	callback_node* node;

	PR_ASSERT (gen && csn);

	slapi_rwlock_rdlock (gen->callbacks.lock);
	node = (callback_node*)dl_get_first (gen->callbacks.list, &cookie);
	while (node)
	{
		if (abort)
		{
			if (node->abort_fn)
				node->abort_fn (csn, node->abort_arg);
		}
		else
		{
			if (node->gen_fn)
				node->gen_fn (csn, node->gen_arg);
		}
		node = (callback_node*)dl_get_next (gen->callbacks.list, &cookie);
	}

	slapi_rwlock_unlock (gen->callbacks.lock);
}

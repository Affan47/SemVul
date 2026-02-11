do_another_auth(private_ike_auth_t *this)
{
	bool do_another = FALSE;
	enumerator_t *done, *todo;
	auth_cfg_t *done_cfg, *todo_cfg;

	if (!this->ike_sa->supports_extension(this->ike_sa, EXT_MULTIPLE_AUTH))
	{
		return FALSE;
	}

	done = this->ike_sa->create_auth_cfg_enumerator(this->ike_sa, TRUE);
	todo = this->peer_cfg->create_auth_cfg_enumerator(this->peer_cfg, TRUE);
	while (todo->enumerate(todo, &todo_cfg))
	{
		if (!done->enumerate(done, &done_cfg))
		{
			done_cfg = this->ike_sa->get_auth_cfg(this->ike_sa, TRUE);
		}
		if (!done_cfg->complies(done_cfg, todo_cfg, FALSE))
		{
			do_another = TRUE;
			break;
		}
	}
	done->destroy(done);
	todo->destroy(todo);
	return do_another;
}

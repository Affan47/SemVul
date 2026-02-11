__nisbind_next (dir_binding *bind)
{
  if (bind->clnt != NULL)
    {
      if (bind->use_auth)
	auth_destroy (bind->clnt->cl_auth);
      clnt_destroy (bind->clnt);
      bind->clnt = NULL;
    }

  if (bind->trys >= bind->server_len)
    return NIS_FAIL;

  for (u_int j = bind->current_ep + 1;
       j < bind->server_val[bind->server_used].ep.ep_len; ++j)
    if (strcmp (bind->server_val[bind->server_used].ep.ep_val[j].family,
		"inet") == 0)
      if (bind->server_val[bind->server_used].ep.ep_val[j].proto[0] == '-')
	{
	  bind->current_ep = j;
	  return NIS_SUCCESS;
	}

  ++bind->trys;
  ++bind->server_used;
  if (bind->server_used >= bind->server_len)
    bind->server_used = 0;

  for (u_int j = 0; j < bind->server_val[bind->server_used].ep.ep_len; ++j)
    if (strcmp (bind->server_val[bind->server_used].ep.ep_val[j].family,
		"inet") == 0)
      if (bind->server_val[bind->server_used].ep.ep_val[j].proto[0] == '-')
	{
	  bind->current_ep = j;
	  return NIS_SUCCESS;
	}

  return NIS_FAIL;
}

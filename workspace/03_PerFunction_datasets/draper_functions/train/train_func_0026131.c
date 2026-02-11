do_sieve_error(int ret,
			  sieve_interp_t *interp,
			  struct hash_table *body_cache,
			  void *script_context,
			  void *message_context,
			  sieve_imapflags_t * imapflags,
			  action_list_t *actions,
			  notify_list_t *notify_list,

			  int lastaction,
			  int implicit_keep,
			  char *actions_string,
			  const char *errmsg
			  )
{
   if (ret != SIEVE_OK) {
	if (lastaction == -1)
	    snprintf(actions_string+strlen(actions_string),
		     ACTIONS_STRING_LEN-strlen(actions_string),
		     "script execution failed: %s\n",
		     errmsg ? errmsg : sieve_errstr(ret));
	else
	    snprintf(actions_string+strlen(actions_string),
		     ACTIONS_STRING_LEN-strlen(actions_string),
		     "%s action failed: %s\n",
		     action_to_string(lastaction),
		     errmsg ? errmsg : sieve_errstr(ret));
    }


    if (interp->notify && notify_list)
      {
	notify_list_t *n = notify_list;
	int notify_ret = SIEVE_OK;

	while (n != NULL)
	  {
	    if (n->isactive)
	      {
	      lastaction = ACTION_NOTIFY;
	       notify_ret = send_notify_callback(interp, body_cache,
						 message_context,
						 script_context,n,
						 actions_string, &errmsg);
	      ret |= notify_ret;
	      }
	    n = n->next;
	  }

	if (notify_list) free_notify_list(notify_list);
	notify_list = NULL;


	if (notify_ret != SIEVE_OK)
	  return do_sieve_error(ret, interp, body_cache,
				script_context, message_context,
				imapflags, actions, notify_list, lastaction,
				implicit_keep, actions_string, errmsg);

      }

    if ((ret != SIEVE_OK) && interp->err) {
	char buf[1024];
	if (lastaction == -1)
	    sprintf(buf, "%s", errmsg ? errmsg : sieve_errstr(ret));
	else
	    sprintf(buf, "%s: %s", action_to_string(lastaction),
		    errmsg ? errmsg : sieve_errstr(ret));

	ret |= interp->execute_err(buf, interp->interp_context,
				   script_context, message_context);
    }

    if (implicit_keep) {
	sieve_keep_context_t keep_context;
	int keep_ret;
	keep_context.imapflags = imapflags;

	lastaction = ACTION_KEEP;
	keep_ret = interp->keep(&keep_context, interp->interp_context,
				script_context, message_context, &errmsg);
	ret |= keep_ret;
        if (keep_ret == SIEVE_OK)
            snprintf(actions_string+strlen(actions_string),
		     sizeof(actions_string)-strlen(actions_string),
		     "Kept\n");
	else {
	    implicit_keep = 0;
	    return do_sieve_error(ret, interp, body_cache,
				  script_context, message_context,
				  imapflags, actions, notify_list, lastaction,
				  implicit_keep, actions_string, errmsg);
	}
    }

    if (actions)
	free_action_list(actions);

    return ret;
}

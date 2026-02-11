config_parser_handle_int(struct list_head *head, void *data)
{
	struct ptoken *t, *first;
	int *target = data;
	char *endp;
	long long tmp;

	first = list_entry(head->next, struct ptoken, list);
	t = config_token_after_equal(head);
	if(!t) {
		logg(LOGF_NOTICE, "Parsing config file %s@%zu: Option \"%s\" wants a value assigned, will ignore\n",
		     first->ctx->in_filename, first->ctx->line_num, first->d.t);
		return true;
	}
	tmp = strtoll(t->d.t, &endp, 0);
	if(t->d.t == endp) {
		logg(LOGF_NOTICE, "Parsing config file %s@%zu: Option \"%s\" wants a numerical value, not \"%s\", will ignore\n",
		     first->ctx->in_filename, first->ctx->line_num, first->d.t, endp);
		return true;
	}
	if(*endp)
		logg(LOGF_INFO, "Parsing config file %s@%zu: Junk (\"%s\") after numerical value %lli, hopefully OK\n",
		     first->ctx->in_filename, first->ctx->line_num, endp, tmp);
	if(tmp < INT_MIN || tmp > INT_MAX) {
		logg(LOGF_NOTICE, "Parsing config file %s@%zu:  Value \"%s\" is to large for option \"%s\", will ignore\n",
		     first->ctx->in_filename, first->ctx->line_num, t->d.t, first->d.t);
		return true;
	}
	*target = (int)tmp;
	if(!list_is_last(&t->list, head))
		logg(LOGF_INFO, "Parsing config file %s@%zu: ignored tokens after \"%s\", hopefully OK\n",
		     first->ctx->in_filename, first->ctx->line_num, t->d.t);
	return true;
}

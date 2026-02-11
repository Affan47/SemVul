krb5_name_canon_iterate(krb5_context context,
			krb5_name_canon_iterator *iter,
			krb5_name_canon_rule_options *rule_opts)
{
    krb5_error_code ret;
    krb5_name_canon_iterator state = *iter;

    if (rule_opts)
	*rule_opts = 0;

    if (!state)
	return 0;
    if (state->done) {
	krb5_free_name_canon_iterator(context, state);
	*iter = NULL;
	return 0;
    }

    if (state->is_trivial && !state->done) {
	state->done = 1;
	return 0;
    }

    do {
	krb5_free_principal(context, state->tmp_princ);
	ret = _krb5_apply_name_canon_rule(context, state->rule,
	    state->in_princ, &state->tmp_princ, rule_opts);
	if (ret)
	    return ret;
	state->rule = state->rule->next;
    } while (state->rule != NULL && state->tmp_princ == NULL);

    if (state->tmp_princ == NULL) {
	krb5_free_name_canon_iterator(context, state);
	*iter = NULL;
	return 0;
    }
    if (state->creds)
	state->creds->server = state->tmp_princ;
    if (state->rule == NULL)
	state->done = 1;
    return 0;
}

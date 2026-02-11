evaluate_option_cache (result, packet, lease, client_state,
			   in_options, cfg_options, scope, oc, file, line)
	struct data_string *result;
	struct packet *packet;
	struct lease *lease;
	struct client_state *client_state;
	struct option_state *in_options;
	struct option_state *cfg_options;
	struct binding_scope **scope;
	struct option_cache *oc;
	const char *file;
	int line;
{
	if (oc->data.data != NULL) {
		data_string_copy (result, &oc -> data, file, line);
		return 1;
	}
	if (!oc -> expression)
		return 0;
	return evaluate_data_expression (result, packet, lease, client_state,
					 in_options, cfg_options, scope,
					 oc -> expression, file, line);
}

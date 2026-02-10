option_space_foreach (struct packet *packet, struct lease *lease,
			   struct client_state *client_state,
			   struct option_state *in_options,
			   struct option_state *cfg_options,
			   struct binding_scope **scope,
			   struct universe *u, void *stuff,
			   void (*func) (struct option_cache *,
					 struct packet *,
					 struct lease *, struct client_state *,
					 struct option_state *,
					 struct option_state *,
					 struct binding_scope **,
					 struct universe *, void *))
{
	if (u -> foreach)
		(*u -> foreach) (packet, lease, client_state, in_options,
				 cfg_options, scope, u, stuff, func);
}

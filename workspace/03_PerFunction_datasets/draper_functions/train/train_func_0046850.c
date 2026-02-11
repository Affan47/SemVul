lookup_linked_option (universe, options, code)
	struct universe *universe;
	struct option_state *options;
	unsigned code;
{
	pair oc;
	struct option_chain_head *head;

	if (universe -> index >= options -> universe_count)
		return 0;
	head = ((struct option_chain_head *)
		options -> universes [universe -> index]);
	if (!head)
		return 0;

	for (oc = head -> first; oc; oc = oc -> cdr) {
		if (code ==
		    ((struct option_cache *)(oc -> car)) -> option -> code) {
			return (struct option_cache *)(oc -> car);
		}
	}

	return (struct option_cache *)0;
}

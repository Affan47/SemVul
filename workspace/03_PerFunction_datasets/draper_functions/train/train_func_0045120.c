new_lease_state (file, line)
	const char *file;
	int line;
{
	struct lease_state *rval;

	if (free_lease_states) {
		rval = free_lease_states;
		free_lease_states =
			(struct lease_state *)(free_lease_states -> next);
 		dmalloc_reuse (rval, file, line, 0);
	} else {
		rval = dmalloc (sizeof (struct lease_state), file, line);
		if (!rval)
			return rval;
	}
	memset (rval, 0, sizeof *rval);
	if (!option_state_allocate (&rval -> options, file, line)) {
		free_lease_state (rval, file, line);
		return (struct lease_state *)0;
	}
	return rval;
}

_node_state_list (void)
{
	int i;
	static char *all_states = NULL;

	if (all_states)
		return (all_states);

	all_states = xstrdup (node_state_string_compact (0));
	for (i = 1; i < NODE_STATE_END; i++) {
		xstrcat (all_states, ",");
		xstrcat (all_states, node_state_string(i));
	}

	xstrcat(all_states, ",DRAIN,DRAINED,DRAINING,NO_RESPOND");
	xstrcat(all_states, ",");
	xstrcat(all_states, node_state_string(NODE_STATE_COMPLETING));
	xstrcat(all_states, ",");
	xstrcat(all_states, node_state_string(NODE_STATE_POWER_SAVE));
	xstrcat(all_states, ",");
	xstrcat(all_states, node_state_string(NODE_STATE_FAIL));
	xstrcat(all_states, ",");
	xstrcat(all_states, node_state_string(NODE_STATE_MAINT));

	for (i = 0; i < strlen (all_states); i++)
		all_states[i] = tolower (all_states[i]);

	return (all_states);
}

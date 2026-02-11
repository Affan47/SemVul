option_parse_group(struct option_state *state)
{
	char *argument = state->argv[state->optpos];
	int l = strlen(argument);
	int i;
	state->grppos++;
	for (i=0; i<state->option_count; i++)
	{
		if (argument[state->grppos] == state->options[i].key)
		{
			if (state->grppos == (l-1))
			{
				state->grppos = 0;
				state->optpos++;
			}
			return state->options[i].key;
		}
	}
	fprintf(stderr, "invalid option: %c\n", argument[state->grppos]);
	exit(1);
}

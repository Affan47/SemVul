system_state_name(enum tgt_system_state state)
{
	int i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(system_state); i++) {
		if (system_state[i].value == state) {
			name = system_state[i].name;
			break;
		}
	}
	return name;
}

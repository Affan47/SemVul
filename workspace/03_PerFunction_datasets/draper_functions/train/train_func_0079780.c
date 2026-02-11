dotconf_is_wild_card(char value)
{
	int retval = 0;
	int i;
	int wildcards_len = strlen(WILDCARDS);

	for (i = 0; i < wildcards_len; i++) {
		if (value == WILDCARDS[i]) {
			retval = 1;
			break;
		}
	}

	return retval;
}

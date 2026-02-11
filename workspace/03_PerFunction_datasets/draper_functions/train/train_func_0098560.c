list_rules()
{
	int i;

	if (!(replace->flags & LIST_X))
		printf("Bridge table: %s\n", table->name);
	if (replace->selected_chain != -1)
		list_em(ebt_to_chain(replace));
	else {

		if (replace->flags & LIST_X && replace->num_chains > NF_BR_NUMHOOKS) {
			for (i = NF_BR_NUMHOOKS; i < replace->num_chains; i++)
				printf("ebtables -t %s -N %s\n", replace->name, replace->chains[i]->name);
			for (i = 0; i < NF_BR_NUMHOOKS; i++)
				if (replace->chains[i] && strcmp(replace->chains[i]->name, ebt_hooknames[i]))
					printf("ebtables -t %s -E %s %s\n", replace->name, ebt_hooknames[i], replace->chains[i]->name);
		}
		for (i = 0; i < replace->num_chains; i++)
			if (replace->chains[i])
				list_em(replace->chains[i]);
	}
}

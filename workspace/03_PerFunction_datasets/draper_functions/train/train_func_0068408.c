set_priorities(struct ael_extension *exten)
{
	int i;
	struct ael_priority *pr;
	do {
		if (exten->is_switch)
			i = 10;
		else if (exten->regexten)
			i=2;
		else
			i=1;

		for (pr=exten->plist; pr; pr=pr->next) {
			pr->priority_num = i;

			if (!pr->origin || (pr->origin && pr->origin->type != PV_LABEL) )


				i++;
		}

		exten = exten->next_exten;
	} while ( exten );
}

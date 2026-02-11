cf_section2xml(FILE *fp, const CONF_SECTION *cs)
{
	CONF_ITEM *ci, *next;


	fprintf(fp, "<%s>\n", cs->name1);
	if (cs->name2) {
		fprintf(fp, "<_name2>%s</_name2>\n", cs->name2);
	}


	for (ci = cs->children; ci; ci = next) {
		next = ci->next;

		switch (ci->type) {
		case CONF_ITEM_PAIR:
			if (!cf_pair2xml(fp, (CONF_PAIR *) ci)) return 0;
			break;

		case CONF_ITEM_SECTION:
			if (!cf_section2xml(fp, (CONF_SECTION *) ci)) return 0;
			break;

		default:
			break;

		}
	}

	fprintf(fp, "</%s>\n", cs->name1);

	return 1;
}

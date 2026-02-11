print_flags(FILE *fp, const struct flag2str *tab, u_int flags, int par)
{
	int first = 1;

	if (par)
		fprintf(fp, "(");
	while (tab->str != NULL) {
		if (flags & tab->flag) {
			if (!first)
				fprintf(fp, par ? "|" : " ");
			first = 0;
			fprintf(fp, "%s", tab->str);
		}
		tab++;
	}
	if (par)
		fprintf(fp, ")");
}

vi_print_generic_keyvalbar_report(FILE *fp, char *title, char *subtitle,
		char *info, int maxlines,
		struct hashtable *ht,
		int(*compar)(const void *, const void *))
{
	int items = ht_used(ht), i, max = 0, tot = 0;
	void **table;

	Output->print_title(fp, title);
	Output->print_subtitle(fp, subtitle);
	Output->print_numkey_info(fp, info, items);
	if ((table = ht_get_array(ht)) == NULL) {
		fprintf(stderr, "Out of memory in print_generic_report()\n");
		return;
	}
	qsort(table, items, sizeof(void*)*2, compar);
	for (i = 0; i < items; i++) {
		long value = (long) table[(i*2)+1];
		tot += value;
		if (value > max) max = value;
	}
	for (i = 0; i < items; i++) {
		char *key = table[i*2];
		long value = (long) table[(i*2)+1];
		if (i >= maxlines) break;
		if (key[0] == '\0')
			Output->print_numkeybar_entry(fp, "none", max, tot, value);
		else
			Output->print_numkeybar_entry(fp, key, max, tot, value);
	}
	free(table);
}

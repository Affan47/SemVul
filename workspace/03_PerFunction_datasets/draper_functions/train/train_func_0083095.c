cb_list_mnemonics (void)
{
	size_t		i;

	printf ("Mnemonic names\n\n");
	for (i = 0; system_table[i].name != NULL; ++i) {
		printf ("%s\n", system_table[i].name);
	}
}

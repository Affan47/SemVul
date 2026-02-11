do_wordlist_pass(struct db_main *db)
{
	char *name;

	if (!(name = cfg_get_param(SECTION_OPTIONS, NULL, "Wordlist")))
	if (!(name = cfg_get_param(SECTION_OPTIONS, NULL, "Wordfile")))
		name = WORDLIST_NAME;

	do_wordlist_crack(db, name, 1);
}

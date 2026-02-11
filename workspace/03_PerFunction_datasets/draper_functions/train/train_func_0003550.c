direntry_check_item(struct item_head *ih, char *item)
{
	int i;
	struct reiserfs_de_head *deh;


	deh = (struct reiserfs_de_head *)item;
	for (i = 0; i < ih_entry_count(ih); i++, deh++) {
		;
	}
}

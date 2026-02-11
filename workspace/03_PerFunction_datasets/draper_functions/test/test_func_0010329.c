desc_ego_fake(int oid)
{

	const char *cursed[] = { "permanently cursed", "heavily cursed", "cursed" };
	const char *xtra[] = { "sustain", "higher resistance", "ability" };
	int i;

	int e_idx = default_join[oid].oid;
	ego_item_type *e_ptr = &e_info[e_idx];

	object_type dummy;
	WIPE(&dummy, dummy);


	screen_save();


	text_out_hook = text_out_to_screen;


	c_prt(TERM_L_BLUE, format("%s %s", ego_grp_name(default_group(oid)),
	                                   e_name + e_ptr->name), 0, 0);


	Term_gotoxy(0, 1);
	text_out("\n");

	if (e_ptr->text)
	{
		int x, y;
		text_out("%s", e_text + e_ptr->text);
		Term_locate(&x, &y);
		Term_gotoxy(0, y+1);
	}


	dummy.name2 = e_idx;
	dummy.tval = e_ptr->tval[0];
	object_info(&dummy, OINFO_FULL | OINFO_DUMMY);

	if (e_ptr->xtra)
		text_out(format("It provides one random %s.", xtra[e_ptr->xtra - 1]));

	if (flags_test(e_ptr->flags, OF_SIZE, OF_CURSE_MASK, FLAG_END))
	{
		if (of_has(e_ptr->flags, OF_PERMA_CURSE))
			i = 0;
		else if (of_has(e_ptr->flags, OF_PERMA_CURSE))
			i = 1;
		else
			i = 2;

		text_out_c(TERM_RED, format("It is %s.", cursed[i]));
	}

	text_out_c(TERM_L_BLUE, "\n\n[Press any key to continue]\n");
	(void)anykey();

	screen_load();
}

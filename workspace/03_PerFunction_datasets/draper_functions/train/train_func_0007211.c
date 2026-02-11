do_cmd_study_book(cmd_code code, cmd_arg args[])
{
	int book = args[0].item;
	object_type *o_ptr = object_from_item_idx(book);

	int spell = -1;
	int i, k = 0;

	cptr p = ((cp_ptr->spell_book == TV_MAGIC_BOOK) ? "spell" : "prayer");


	if (!player_can_study())
		return;


	if (!item_is_available(book, obj_can_browse, (USE_INVEN | USE_FLOOR)))
	{
		msg_format("That item is not within your reach.");
		return;
	}


	for (i = 0; i < SPELLS_PER_BOOK; i++)
	{
		int s = get_spell_index(o_ptr, i);


		if (s == -1) continue;
		if (!spell_okay(s, FALSE, FALSE)) continue;


		if ((++k > 1) && (randint0(k) != 0)) continue;


		spell = s;
	}

	if (spell < 0)
	{
		msg_format("You cannot learn any %ss in that book.", p);
	}
	else
	{
		spell_learn(spell);
		p_ptr->energy_use = 100;
	}
}

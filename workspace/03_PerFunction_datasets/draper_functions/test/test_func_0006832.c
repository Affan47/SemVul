py_pickup_gold(void)
{
	int py = p_ptr->py;
	int px = p_ptr->px;

	s32b total_gold = 0L;
	byte *treasure;

	s16b this_o_idx = 0;
	s16b next_o_idx = 0;

	object_type *o_ptr;

	int sound_msg;
	bool verbal = FALSE;


	treasure = C_ZNEW(SV_GOLD_MAX, byte);


	for (this_o_idx = cave->o_idx[py][px]; this_o_idx; this_o_idx = next_o_idx)
	{

		o_ptr = object_byid(this_o_idx);


		next_o_idx = o_ptr->next_o_idx;


		if ((o_ptr->tval != TV_GOLD) ||
		    (o_ptr->sval >= SV_GOLD_MAX)) continue;


		treasure[o_ptr->sval]++;


		if (!squelch_item_ok(o_ptr))
			verbal = TRUE;


		total_gold += (s32b)o_ptr->pval[DEFAULT_PVAL];


		delete_object_idx(this_o_idx);
	}


	if (total_gold)
	{
		char buf[1024];
		char tmp[80];
		int i, count, total;
		object_kind *kind;


		(void)strnfmt(buf, sizeof(buf), "You have found %ld gold pieces worth of ", (long)total_gold);


		for (total = 0, i = 0; i < SV_GOLD_MAX; i++)
		{
			if (treasure[i]) total++;
		}


		for (count = 0, i = 0; i < SV_GOLD_MAX; i++)
		{

			if (!treasure[i]) continue;


			kind = lookup_kind(TV_GOLD, i);
			if (!kind) continue;


			object_kind_name(tmp, sizeof tmp, kind, TRUE);


			my_strcat(buf, tmp, sizeof(buf));


			count++;


			if ((total > 2) && (count < total)) my_strcat(buf, ",", sizeof(buf));


			if ((total >= 2) && (count == total-1)) my_strcat(buf, " and", sizeof(buf));


			if (count < total) my_strcat(buf, " ", sizeof(buf));
			else               my_strcat(buf, ".", sizeof(buf));
		}


		if      (total_gold < 200) sound_msg = MSG_MONEY1;
		else if (total_gold < 600) sound_msg = MSG_MONEY2;
		else                       sound_msg = MSG_MONEY3;


		if (verbal)
			msgt(sound_msg, "%s", buf);


		p_ptr->au += total_gold;


		p_ptr->redraw |= (PR_GOLD);
	}


	FREE(treasure);
}

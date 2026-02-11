reorder_pack(void)
{
	int i, j, k;

	s32b o_value;
	s32b j_value;

	object_type *o_ptr;
	object_type *j_ptr;

	object_type *i_ptr;
	object_type object_type_body;

	bool flag = FALSE;


	for (i = 0; i < INVEN_PACK; i++)
	{

		o_ptr = &p_ptr->inventory[i];


		if (!o_ptr->kind) continue;


		o_value = o_ptr->kind->cost;


		for (j = 0; j < INVEN_PACK; j++)
		{

			j_ptr = &p_ptr->inventory[j];


			if (!j_ptr->kind) break;


			if ((o_ptr->tval == p_ptr->class->spell_book) &&
			    (j_ptr->tval != p_ptr->class->spell_book)) break;
			if ((j_ptr->tval == p_ptr->class->spell_book) &&
			    (o_ptr->tval != p_ptr->class->spell_book)) continue;


			if (o_ptr->tval > j_ptr->tval) break;
			if (o_ptr->tval < j_ptr->tval) continue;


			if (!object_flavor_is_aware(o_ptr)) continue;
			if (!object_flavor_is_aware(j_ptr)) break;


			if (o_ptr->sval < j_ptr->sval) break;
			if (o_ptr->sval > j_ptr->sval) continue;


			if (!object_is_known(o_ptr)) continue;
			if (!object_is_known(j_ptr)) break;


			if (o_ptr->tval == TV_LIGHT)
			{
				if (o_ptr->pval[DEFAULT_PVAL] > j_ptr->pval[DEFAULT_PVAL]) break;
				if (o_ptr->pval[DEFAULT_PVAL] < j_ptr->pval[DEFAULT_PVAL]) continue;
			}


			j_value = j_ptr->kind->cost;


			if (o_value > j_value) break;
			if (o_value < j_value) continue;
		}


		if (j >= i) continue;


		flag = TRUE;


		i_ptr = &object_type_body;


		object_copy(i_ptr, &p_ptr->inventory[i]);


		for (k = i; k > j; k--)
		{

			object_copy(&p_ptr->inventory[k], &p_ptr->inventory[k-1]);


			if (tracked_object_is(k-1))
			{
				track_object(k);
			}
		}


		object_copy(&p_ptr->inventory[j], i_ptr);


		if (tracked_object_is(i))
		{
			track_object(j);
		}


		p_ptr->redraw |= (PR_INVEN);
	}

	if (flag)
	{
		msg("You reorder some items in your pack.");


		cmd_disable_repeat();
	}
}

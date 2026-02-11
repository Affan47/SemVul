death_knowledge(void)
{
	store_type *st_ptr = &store[STORE_HOME];
	object_type *o_ptr;

	int i;

	for (i = 0; i < ALL_INVEN_TOTAL; i++)
	{
		o_ptr = &inventory[i];
		if (!o_ptr->k_idx) continue;

		object_flavor_aware(o_ptr);
		object_notice_everything(o_ptr);
	}

	for (i = 0; i < st_ptr->stock_num; i++)
	{
		o_ptr = &st_ptr->stock[i];
		if (!o_ptr->k_idx) continue;

		object_flavor_aware(o_ptr);
		object_notice_everything(o_ptr);
	}

	history_unmask_unknown();


	p_ptr->update |= (PU_BONUS);
	handle_stuff();
}

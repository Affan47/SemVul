identify_pack(void)
{
	int i;


	for (i = 0; i < ALL_INVEN_TOTAL; i++)
	{
		object_type *o_ptr = &p_ptr->inventory[i];


		if (!o_ptr->kind) continue;


		if (object_is_known(o_ptr)) continue;


		do_ident_item(i, o_ptr);


		i--;
	}
}

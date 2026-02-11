squelch_drop(void)
{
	int n;


	for (n = INVEN_PACK - 1; n >= 0; n--)
	{
		object_type *o_ptr = &p_ptr->inventory[n];


		if (!o_ptr->kind) continue;
		if (!squelch_item_ok(o_ptr)) continue;


		if (!check_for_inscrip(o_ptr, "!d") && !check_for_inscrip(o_ptr, "!*"))
		{

			inven_drop(n, o_ptr->number);
		}
	}


	p_ptr->notice |= (PN_COMBINE | PN_REORDER);
}

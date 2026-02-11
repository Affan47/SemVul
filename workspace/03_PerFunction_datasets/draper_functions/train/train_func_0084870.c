inv_slot(char *str, size_t len, int i, bool equip)
{
	object_type *o_ptr;
	char o_name[80], label[5];
	int name_size = 80;


	o_ptr = &p_ptr->inventory[i];


	if (item_tester_okay(o_ptr) || equip)
	{

		object_desc(o_name, sizeof(o_name), o_ptr, ODESC_PREFIX | ODESC_FULL);


		strnfmt(label, sizeof(label), "%c) ", index_to_label(i));

		if (equip)
			name_size = name_size - 19;


		if (o_ptr->weight)
		{
			int wgt = o_ptr->weight * o_ptr->number;
			name_size = name_size - 4 - 9 - 9 - 5;

			if (equip)
				strnfmt(str, len, "%s%-*s %3d.%1d lb <-- %s", label, name_size, o_name, wgt / 10, wgt % 10, mention_use(i));
			else
				strnfmt(str, len, "%s%-*s %3d.%1d lb", label, name_size, o_name, wgt / 10, wgt % 10);
		}
		else
		{
			name_size = name_size - 4 - 9 - 5;

			if (equip)
				strnfmt(str, len, "%s%-*s <-- %s", label, name_size, o_name, mention_use(i));
			else
				strnfmt(str, len, "%s%-*s", label, name_size, o_name);
		}
	}
}

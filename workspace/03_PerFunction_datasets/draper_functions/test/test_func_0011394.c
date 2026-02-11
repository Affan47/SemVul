object_value_base(const object_type *o_ptr)
{
	object_kind *k_ptr = &k_info[o_ptr->k_idx];


	if (object_flavor_is_aware(o_ptr) || o_ptr->ident & IDENT_STORE)
		return k_ptr->cost;


	switch (o_ptr->tval)
	{
		case TV_FOOD:
			return 5;
		case TV_POTION:
		case TV_SCROLL:
			return 20;
		case TV_RING:
		case TV_AMULET:
			return 45;
		case TV_WAND:
			return 50;
		case TV_STAFF:
			return 70;
		case TV_ROD:
			return 90;
	}

	return 0;
}

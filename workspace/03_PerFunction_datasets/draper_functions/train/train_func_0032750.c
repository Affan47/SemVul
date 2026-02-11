find_free_slot_in(U_I table_integer) const
    {
	U_I ret = 0;
	U_64 focus = alloc_table[table_integer];


	while(focus > HALF)
	{
	    focus <<= 1;
	    ++ret;
	}

	return ret;
    }

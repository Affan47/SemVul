lookup_monster(const char *name)
{
	int i;


	for (i = 1; i < z_info->r_max; i++)
	{
		monster_race *r_ptr = &r_info[i];
		const char *nm = r_name + r_ptr->name;


		if (streq(name, nm))
			return i;

	}

	return -1;
}

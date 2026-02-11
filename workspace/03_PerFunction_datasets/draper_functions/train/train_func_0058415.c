get_obj_num(int level, bool good)
{

	size_t ind, item;
	u32b value;


	if ((level > 0) && one_in_(GREAT_OBJ))
	{

		level = 1 + (level * MAX_O_DEPTH / randint1(MAX_O_DEPTH));
	}


	level = MIN(level, MAX_O_DEPTH);
	level = MAX(level, 0);


	ind = level * z_info->k_max;

	if (!good)
	{
		value = randint0(obj_total[level]);
		for (item = 1; item < z_info->k_max; item++)
		{

			if (value < obj_alloc[ind + item]) break;


			value -= obj_alloc[ind + item];
		}
	}
	else
	{
		value = randint0(obj_total_great[level]);
		for (item = 1; item < z_info->k_max; item++)
		{

			if (value < obj_alloc_great[ind + item]) break;


			value -= obj_alloc_great[ind + item];
		}
	}


	return objkind_byid(item);
}

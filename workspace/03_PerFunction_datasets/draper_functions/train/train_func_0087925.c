Rand_simple(u32b m)
{
	static bool initialized = FALSE;
	static u32b simple_rand_value;
	bool old_rand_quick;
	u32b old_rand_value;
	u32b result;


	old_rand_quick = Rand_quick;
	old_rand_value = Rand_value;


	Rand_quick = TRUE;

	if (initialized)
	{

		Rand_value = simple_rand_value;
	}
	else
	{

		Rand_value = time(NULL);
		initialized = TRUE;
	}


	result = randint0(m);


	simple_rand_value = Rand_value;


	Rand_quick = old_rand_quick;
	Rand_value = old_rand_value;


	return (result);
}

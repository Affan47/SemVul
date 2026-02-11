place_random_stairs(int y, int x)
{

	if (!cave_clean_bold(y, x)) return;


	if (!p_ptr->depth)
	{
		place_down_stairs(y, x);
	}
	else if (is_quest(p_ptr->depth) || (p_ptr->depth >= MAX_DEPTH-1))
	{
		place_up_stairs(y, x);
	}
	else if (randint0(100) < 50)
	{
		place_down_stairs(y, x);
	}
	else
	{
		place_up_stairs(y, x);
	}
}

stair_creation(void)
{
	int py = p_ptr->py;
	int px = p_ptr->px;


	if (cave->feat[py][px] != FEAT_FLOOR)
	{
		msg("There is no empty floor here.");
		return;
	}


	if (cave->o_idx[py][px]) push_object(py, px);


	if (!p_ptr->depth)
	{
		cave_set_feat(cave, py, px, FEAT_MORE);
	}
	else if (is_quest(p_ptr->depth) || (p_ptr->depth >= MAX_DEPTH-1))
	{
		cave_set_feat(cave, py, px, FEAT_LESS);
	}
	else if (randint0(100) < 50)
	{
		cave_set_feat(cave, py, px, FEAT_MORE);
	}
	else
	{
		cave_set_feat(cave, py, px, FEAT_LESS);
	}
}

pick_trap(int y, int x)
{
	int feat;

	static const int min_level[] =
	{
		2,
		2,
		2,
		2,
		3,
		1,
		2,
		2,
		2,
		6,
		6,
		6,
		2,
		1,
		2,
		2,
	};


	if (cave_feat[y][x] != FEAT_INVIS) return;


	while (1)
	{

		feat = FEAT_TRAP_HEAD + randint0(16);


		if (min_level[feat - FEAT_TRAP_HEAD] > p_ptr->depth) continue;


		if ((feat == FEAT_TRAP_HEAD + 0x00) && is_quest(p_ptr->depth)) continue;


		if ((feat == FEAT_TRAP_HEAD + 0x00) && (p_ptr->depth >= MAX_DEPTH-1)) continue;


		break;
	}


	cave_set_feat(y, x, feat);
}

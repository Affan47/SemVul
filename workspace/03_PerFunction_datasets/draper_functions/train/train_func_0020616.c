smash_obstacles_only_on_tile(float x, float y, int level, int map_x, int map_y)
{
	Level BoxLevel = curShip.AllLevels[level];
	int i;
	int target_idx;
	obstacle *target_obstacle;
	int smashed_something = FALSE;
	moderately_finepoint blast_start_pos;


	if (!pos_inside_level(map_x, map_y, BoxLevel))
		return (FALSE);


	for (i = 0; i < BoxLevel->map[map_y][map_x].glued_obstacles.size; i++) {


		target_idx = ((int *)(BoxLevel->map[map_y][map_x].glued_obstacles.arr))[i];

		target_obstacle = &(BoxLevel->obstacle_list[target_idx]);

		obstacle_spec *obstacle_spec = get_obstacle_spec(target_obstacle->type);
		if (!(obstacle_spec->flags & IS_SMASHABLE))
			continue;


		if (fabsf(x - target_obstacle->pos.x) > 0.4)
			continue;
		if (fabsf(y - target_obstacle->pos.y) > 0.4)
			continue;

		colldet_filter filter = FlyableExceptIdPassFilter;
		filter.data = &target_idx;
		gps smash_pos = { x, y, level };
		gps vsmash_pos;
		update_virtual_position(&vsmash_pos, &smash_pos, Me.pos.z);
		if (vsmash_pos.x == -1)
			continue;
		if (!DirectLineColldet(vsmash_pos.x, vsmash_pos.y, Me.pos.x, Me.pos.y, Me.pos.z, &filter)) {
			continue;
		}

		DebugPrintf(1, "\nObject smashed at: (%f/%f) by hit/explosion at (%f/%f).",
			    target_obstacle->pos.x, target_obstacle->pos.y, x, y);

		smashed_something = TRUE;


		blast_start_pos.x = target_obstacle->pos.x;
		blast_start_pos.y = target_obstacle->pos.y;

		int obstacle_drops_treasure
			= obstacle_spec->flags & DROPS_RANDOM_TREASURE;


		update_obstacle_automap(level, target_obstacle);


		if (obstacle_spec->result_type_after_smashing_once == (-1)) {
			del_obstacle(target_obstacle);
		} else {
			target_obstacle->type = obstacle_spec->result_type_after_smashing_once;
		}


		if (obstacle_drops_treasure)
			DropRandomItem(level, target_obstacle->pos.x, target_obstacle->pos.y, 0, FALSE);


		StartBlast(blast_start_pos.x, blast_start_pos.y, level, DROIDBLAST, 0.0, FACTION_SELF);
	}

	return smashed_something;
}

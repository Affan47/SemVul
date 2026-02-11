rd_dungeon(void)
{
	int i, y, x;

	s16b depth;
	s16b py, px;
	s16b ymax, xmax;

	byte count;
	byte tmp8u;
	u16b tmp16u;


	if (p_ptr->is_dead)
		return 0;


	rd_s16b(&depth);
	rd_u16b(&daycount);
	rd_s16b(&py);
	rd_s16b(&px);
	rd_s16b(&ymax);
	rd_s16b(&xmax);
	rd_u16b(&tmp16u);
	rd_u16b(&tmp16u);


	if ((depth < 0) || (depth >= MAX_DEPTH))
	{
		note(format("Ignoring illegal dungeon depth (%d)", depth));
		return (0);
	}

	cave->width = xmax;
	cave->height = ymax;


	if ((px < 0) || (px >= DUNGEON_WID) ||
	    (py < 0) || (py >= DUNGEON_HGT))
	{
		note(format("Ignoring illegal player location (%d,%d).", py, px));
		return (1);
	}


	for (x = y = 0; y < DUNGEON_HGT; )
	{

		rd_byte(&count);
		rd_byte(&tmp8u);


		for (i = count; i > 0; i--)
		{

			cave->info[y][x] = tmp8u;


			if (++x >= DUNGEON_WID)
			{

				x = 0;


				if (++y >= DUNGEON_HGT) break;
			}
		}
	}


	for (x = y = 0; y < DUNGEON_HGT; )
	{

		rd_byte(&count);
		rd_byte(&tmp8u);


		for (i = count; i > 0; i--)
		{

			cave->info2[y][x] = tmp8u;


			if (++x >= DUNGEON_WID)
			{

				x = 0;


				if (++y >= DUNGEON_HGT) break;
			}
		}
	}


	for (x = y = 0; y < DUNGEON_HGT; )
	{

		rd_byte(&count);
		rd_byte(&tmp8u);


		for (i = count; i > 0; i--)
		{

			cave_set_feat(cave, y, x, tmp8u);


			if (++x >= DUNGEON_WID)
			{

				x = 0;


				if (++y >= DUNGEON_HGT) break;
			}
		}
	}


	p_ptr->depth = depth;


	player_place(cave, p_ptr, py, px);


	character_dungeon = TRUE;

#if 0

	if (p_ptr->depth == 0)
		character_dungeon = FALSE;
#endif

	return 0;
}

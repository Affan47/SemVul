mark_unreachable_places (void)
{
  a_tile_index i;

  for (i = 0; i < lvl.tile_count; ++i) {
    a_square_index s = TILE_INDEX_TO_SQR_INDEX (&lvl, i);


    if ((lvl_tile_type (&lvl, i) == T_OUTWAY)
	|| (lvl.square_walls_out[SQR0 (&lvl, s)] & (DM_DOWN | DM_RIGHT))
	|| (lvl.square_walls_out[SQR1 (&lvl, s)] & (DM_DOWN | DM_LEFT))
	|| (lvl.square_walls_out[SQR2 (&lvl, s)] & (DM_UP | DM_RIGHT))
	|| (lvl.square_walls_out[SQR3 (&lvl, s)] & (DM_UP | DM_LEFT)))
      tile_bonus[i] = 0xff;
  }
}

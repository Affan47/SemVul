reverse_walls (a_level *lvl, const a_dir_mask8 *square_walls_in)
{
  a_square_index idx;

  memset (lvl->square_walls_out, 0, lvl->square_count);

  for (idx = 0; idx < lvl->square_count; ++idx) {
    a_square_index *dest;
    a_dir_mask8 *swo = lvl->square_walls_out + idx;
    bool is_tunnel = (lvl->square_type[idx] == T_TUNNEL);
    a_dir tunnel_dir = lvl->square_direction[idx];


    if (!is_tunnel || tunnel_dir != D_UP) {
      dest = &lvl->square_move[D_UP][idx];
      if ((*dest == INVALID_INDEX) || (square_walls_in[*dest] & DM_UP)) {
	*swo |= DM_UP;
	*dest = INVALID_INDEX;
      }
    }

    if (!is_tunnel || tunnel_dir != D_RIGHT) {
      dest = &lvl->square_move[D_RIGHT][idx];
      if ((*dest == INVALID_INDEX) || (square_walls_in[*dest] & DM_RIGHT)) {
	*swo |= DM_RIGHT;
	*dest = INVALID_INDEX;
      }
    }

    if (!is_tunnel || tunnel_dir != D_DOWN) {
      dest = &lvl->square_move[D_DOWN][idx];
      if ((*dest == INVALID_INDEX) || (square_walls_in[*dest] & DM_DOWN)) {
	*swo |= DM_DOWN;
	*dest = INVALID_INDEX;
      }
    }

    if (!is_tunnel || tunnel_dir != D_LEFT) {
      dest = &lvl->square_move[D_LEFT][idx];
      if ((*dest == INVALID_INDEX) || (square_walls_in[*dest] & DM_LEFT)) {
	*swo |= DM_LEFT;
	*dest = INVALID_INDEX;
      }
    }
  }
}

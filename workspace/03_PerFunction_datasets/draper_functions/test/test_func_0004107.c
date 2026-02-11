next_cell(pgc_t *pgc, int cell, int angle)
  {
  int ret;
  ret = cell;


  if(pgc->cell_playback[ret].block_type == BLOCK_TYPE_ANGLE_BLOCK)
    {
    while(pgc->cell_playback[ret].block_mode != BLOCK_MODE_LAST_CELL)
      ret++;
    }


  ret++;


  if(ret >= pgc->nr_of_cells)
    return -1;


  if(pgc->cell_playback[ret].block_type == BLOCK_TYPE_ANGLE_BLOCK)
    {
    ret += angle;
    }


  return ret;
  }

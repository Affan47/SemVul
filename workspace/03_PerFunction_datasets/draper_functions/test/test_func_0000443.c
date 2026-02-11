get_infos_inversion( int32_t* pos1, int32_t* pos2, int16_t* align_score )
{
  assert( _mut_type == INV );
  *pos1    = _pos[0];
  *pos2    = _pos[1];

  if ( align_score != NULL )
  {
    *align_score = *_align_score;
  }
}

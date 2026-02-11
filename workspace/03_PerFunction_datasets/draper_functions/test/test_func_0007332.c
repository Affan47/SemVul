copy_into_new_GU( int32_t pos_1, int32_t pos_2 ) const
{
  int32_t seq_length = ae_utils::mod( pos_2 - pos_1, _length );
  if ( seq_length == 0 ) seq_length = _length;


  ae_list<ae_rna*>** proms_new_GU  = new ae_list<ae_rna*>*[2];
  proms_new_GU[LEADING]   = new ae_list<ae_rna*>();
  proms_new_GU[LAGGING]   = new ae_list<ae_rna*>();
  _gen_unit->copy_promoters_included_in( pos_1, pos_2, proms_new_GU );
  ae_genetic_unit::shift_promoters( proms_new_GU, -pos_1, _length );


  int32_t length_new_GU     = seq_length;
  char*   sequence_new_GU   = new char[nb_blocks( length_new_GU ) * BLOCK_SIZE];
  if ( pos_1 < pos_2 )
  {
    memcpy( sequence_new_GU, &_data[pos_1], length_new_GU * sizeof(char) );
  }
  else
  {
    memcpy( sequence_new_GU, &_data[pos_1], (_length - pos_1) * sizeof(char) );
    memcpy( &sequence_new_GU[_length - pos_1], &_data[0], pos_2 * sizeof(char) );
  }
  sequence_new_GU[length_new_GU] = '\0';


  ae_genetic_unit* new_GU = new ae_genetic_unit( _indiv, sequence_new_GU, length_new_GU, proms_new_GU );


  new_GU->look_for_new_promoters_around( 0 );

  return new_GU;
}

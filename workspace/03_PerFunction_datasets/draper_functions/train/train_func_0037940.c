invert_promoters_included_in( int32_t pos_1, int32_t pos_2 )
{
  assert( pos_1 >= 0 && pos_1 <= pos_2 && pos_2 <= _dna->get_length() );

  int32_t segment_length = pos_2 - pos_1;

  if ( segment_length >= PROM_SIZE )
  {
    ae_list<ae_rna*>** inverted_promoters = new ae_list<ae_rna*>*[2];
    inverted_promoters[LEADING] = new ae_list<ae_rna*>();
    inverted_promoters[LAGGING] = new ae_list<ae_rna*>();


    extract_promoters_included_in( pos_1, pos_2, inverted_promoters );


    ae_genetic_unit::invert_promoters( inverted_promoters, pos_1, pos_2 );


    insert_promoters( inverted_promoters );

    delete inverted_promoters[LEADING];
    delete inverted_promoters[LAGGING];
    delete [] inverted_promoters;
  }
}

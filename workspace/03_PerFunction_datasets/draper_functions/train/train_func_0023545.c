get_leading_promoters_starting_before( int32_t pos, ae_list<ae_rna*>* leading_promoters )
{
  assert( pos >= 0 && pos < _dna->get_length() );

  ae_list_node<ae_rna*>* rna_node  = _rna_list[LEADING]->get_first();


  while ( rna_node != NULL && rna_node->get_obj()->get_promoter_pos() < pos )
  {
    leading_promoters->add( rna_node->get_obj() );

    rna_node = rna_node->get_next();
  }
}

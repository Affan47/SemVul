extract_lagging_promoters_starting_after( int32_t pos, ae_list<ae_rna*>* extracted_promoters )
{
  assert( pos >= 0 && pos < _dna->get_length() );

  ae_list_node<ae_rna*>* rna_node = NULL;


  rna_node = _rna_list[LAGGING]->get_first();


  ae_list_node<ae_rna*>* node_last = NULL;
  while ( rna_node != NULL && rna_node->get_obj()->get_promoter_pos() >= pos )
  {
    node_last = rna_node;
    rna_node  = rna_node->get_next();
  }

  if ( node_last != NULL )
  {

    ae_list<ae_rna*>* tmp_list = _rna_list[LAGGING]->extract_starting_sublist( node_last );
    extracted_promoters->merge( tmp_list );
    delete tmp_list;
  }
}

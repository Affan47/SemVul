make_protein_list( void )
{
  assert( _protein_list != NULL );


  _protein_list->erase( false );


  ae_list_node<ae_genetic_unit*>* gen_unit_node = _genetic_unit_list->get_first();
  ae_genetic_unit*  gen_unit      = NULL;

  while ( gen_unit_node != NULL )
  {
    gen_unit = gen_unit_node->get_obj();

    _protein_list->add_list( gen_unit->get_protein_list()[LEADING] );
    _protein_list->add_list( gen_unit->get_protein_list()[LAGGING] );

    gen_unit_node = gen_unit_node->get_next();
  }
}

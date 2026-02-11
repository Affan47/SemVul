sort_individuals( void )
{

  ae_list_node<ae_individual*>* last_sorted   = _indivs->get_first();
  ae_list_node<ae_individual*>* comp          = NULL;
  ae_list_node<ae_individual*>* item_to_sort  = NULL;
  double  fit_comp;
  double  fitness_to_sort;
  bool    is_sorted;


  for ( int32_t nb_sorted = 1 ; nb_sorted < _nb_indivs ; nb_sorted++ )
  {
    item_to_sort    = last_sorted->get_next();
    fitness_to_sort = item_to_sort->get_obj()->get_fitness();
    is_sorted       = false;

    comp = last_sorted;


    while ( !is_sorted )
    {
      fit_comp = comp->get_obj()->get_fitness();

      if ( fitness_to_sort >= fit_comp )
      {
        if ( item_to_sort->get_prev() == comp )
        {

          is_sorted = true;
          last_sorted = item_to_sort;
        }


        _indivs->remove( item_to_sort, false, false );
        _indivs->insert_after( item_to_sort, comp );
        is_sorted = true;
      }
      else
      {

        comp = comp->get_prev();
      }

      if ( comp == NULL )
      {

        _indivs->remove( item_to_sort, false, false );
        _indivs->add_front( item_to_sort );
        is_sorted = true;
      }
    }
  }


  ae_list_node<ae_individual*>* indiv_node  = _indivs->get_first();
  ae_individual* indiv       = NULL;

  for ( int32_t rank = 1 ; rank <= _nb_indivs ; rank++ )
  {
    indiv = indiv_node->get_obj();
    indiv->set_rank( rank );
    indiv_node = indiv_node->get_next();
  }

}

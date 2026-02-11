_assert_order( void )
{
  assert( (_points->get_first()->get_obj())->x == X_MIN );
  assert( (_points->get_last()->get_obj())->x == X_MAX );

  ae_list_node<ae_point_2d*>* point_node  = _points->get_first();
  ae_list_node<ae_point_2d*>* next_point_node = point_node->get_next();
  ae_point_2d*  point;
  ae_point_2d*  next_point;

  while ( next_point_node != NULL )
  {
    point = point_node->get_obj();
    next_point = next_point_node->get_obj();

    assert( point->x <= next_point->x );

    point_node = point_node->get_next();
    next_point_node = next_point_node->get_next();
  }
}

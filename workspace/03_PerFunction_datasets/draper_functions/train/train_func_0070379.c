set_grid_cell( ae_grid_cell* grid_cell )
{
  _placed_in_population = true;
  _grid_cell = grid_cell;
  if ( _grid_cell->get_individual() != this )
  {
    _grid_cell->set_individual( this );
  }
}

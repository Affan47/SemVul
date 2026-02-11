check_alloc(int n)
{
  if ( atoms_allocated < n ) {
    for ( int j = 0; j < atoms_allocated; j++ ) {
      delete [] old_velocity[j];
    }
    delete [] old_velocity;

    old_velocity = new double* [n];
    for ( int j = 0; j < n; j++ )
      old_velocity[j] = new double [3];
    atoms_allocated = n;
  }
}

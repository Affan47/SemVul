state_change( AtomList& adds, AtomList& deletes,
				   AssignmentList& assignments,
				   const state_t& state ) const
{
  if( size() != 0 )
    {
      double w = drand48();
      double wtot = 0;
      size_t n = size();
      for( size_t i = 0; i < n; ++i )
	{
	  wtot += weights_[i];
	  if( w < wtot )
	    {
	      effect( i ).state_change( adds, deletes, assignments, state );
	      return;
	    }
	}
    }
}

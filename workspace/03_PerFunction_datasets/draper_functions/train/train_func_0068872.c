affect( const state_t& state_in, state_t& state_out,
			                   ValueMap *vm, bool bMostLikely) const
{
  bool rv = false;
  for( size_t i = 0; i < add_list().size(); ++i )
    rv = state_out.add( add_list().atom( i ) ) || rv;
  for( size_t i = 0; i < del_list().size(); ++i )
    rv = state_out.clear( del_list().atom( i ) ) || rv;
  return( rv );
}

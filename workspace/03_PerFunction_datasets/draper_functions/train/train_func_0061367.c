affect( const state_t& state_in, state_t& state_out,
			                   ValueMap *vm, bool bMostLikely) const
{
  return( precondition().holds( state_in, false ) && effect()->affect(
				       state_in, state_out, vm, bMostLikely ) );
}

set_seqnum( const int s, const String inscode )
{
  if ( inscode != "" ) set_id( String( s, 4 ) + ":" + inscode );
  else                 set_id( String( s, 4 ) );
}

handle_ping (CS* c, Msg * )
{
  c->last_talk = time( 0 );
  if ( c->max_jobs < 0 )
    c->max_jobs *= -1;
  return true;
}

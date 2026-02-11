unscheduleCheck()
{
  char dummy[16];
  if( ::read( d->fd[0], dummy, sizeof(dummy) ) > 0 )
    d->needcheck = true;
}

add_ccp ( CCPCON * _ccp )
{
  int cc;

  for ( cc=0; cc<MAX_PWM_CHANS; cc++ )
  {
    if ( ccp[cc] == 0 || ccp[cc] == _ccp )
    {
        ccp[cc] = _ccp;
        return true;
    }
  }
  return false;
}

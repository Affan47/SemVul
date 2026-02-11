setTimeoutInterval ( double dblTimeout )
{
  int tSec = ( int ) dblTimeout;
  int tMs = ( int ) ( 1000000.0 * ( dblTimeout - tSec ) );
  timeoutInterval.tv_sec  = tSec;
  timeoutInterval.tv_usec = tMs;
  timeoutEnabled = dblTimeout > 0 && timerisset ( &timeoutInterval );

  JASSERT ( gettimeofday ( &stoptime,NULL ) == 0 );
  timeradd ( &timeoutInterval,&stoptime,&stoptime );
}

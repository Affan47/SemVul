artSetMaxBytesInUse (u_int val)
{
  ASSERT (maxBytesInUse > 0) ;
  ASSERT (val > 0) ;

  maxBytesInUse = val ;
}

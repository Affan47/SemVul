reset (void)
{
  back     = NULL;
  distance = 0;
  remains  = LONG_MAX;
  queued   = false;
  tagged   = false;


  if ( !intree ) {
    if ( point.inside() ) {
      point.node().algo = NULL;
      point.unlink ();
    }
  }
}

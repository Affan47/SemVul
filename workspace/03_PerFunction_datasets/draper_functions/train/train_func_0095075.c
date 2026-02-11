listenerConfigLoadCbk (void *data)
{
  int bval ;

  (void) data ;

  if (getBool (topScope,"fast-exit",&bval,NO_INHERIT))
    fastExit = (bval ? true : false) ;

  return 1 ;
}

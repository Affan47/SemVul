Timing(bool h)
{
  if ( timing ) {
    mute = false ;
    show("tme",h) ;
  } else {
    mute = true ;
  }
  return *this ;
}

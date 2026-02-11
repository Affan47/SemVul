Rotation_dump(Rotation rot)
{
  static const char *rstr[4]={"0 deg","90 deg","180 deg","270 deg"};
  if ( (rot<ROT_0)||(rot>ROT_270) ) {
    fprintf(stderr,"(bad rotation: %d)",rot);
  } else {
    fputs(rstr[rot],stderr);
  }
}

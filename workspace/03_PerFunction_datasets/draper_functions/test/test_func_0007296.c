is_tokstren(int32 ttyp)
{
 switch ((byte) ttyp) {
  case SUPPLY0: case STRONG0: case PULL0: case WEAK0: case HIGHZ0:
   return(LOW_STREN);
  case SUPPLY1: case STRONG1: case PULL1: case WEAK1: case HIGHZ1:
   return(HIGH_STREN);
  case SMALL: case MEDIUM: case LARGE:
   return(CAP_STREN);
 }
 return(NO_STREN);
}

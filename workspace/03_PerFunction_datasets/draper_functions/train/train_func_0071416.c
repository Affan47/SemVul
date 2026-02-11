hashkey1(Char *c_addr, UCell u, UCell ubits)


{
  static char rot_values[] = {5,0,1,2,3,4,5,5,5,5,3,5,5,5,5,7,5,5,5,5,7,5,5,5,5,6,5,5,5,5,7,5,5};
  unsigned rot = rot_values[ubits];
  Char *cp = c_addr;
  UCell ukey;

  for (ukey=0; cp<c_addr+u; cp++)
    ukey = ((((ukey<<rot) | (ukey>>(ubits-rot)))
	     ^ toupper(*cp))
	    & ((1<<ubits)-1));
  return ukey;
}

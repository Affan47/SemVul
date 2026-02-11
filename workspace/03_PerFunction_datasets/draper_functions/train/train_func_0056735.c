retarget(int defindex)
{
  int t;
  static int allid[2] = { ALLGEOMS, ALLCAMS };
  static char ch[2] = { 'g', 'c' };
  char code[12];

  if(keymode == KEYNONE) {
    if(number.expon && !number.has) {
      number.expon = 0;
      return TARGETID;
    }
    return prefixid != NOID ?
      prefixid : defindex;
  }

  sprintf(code, "%c%d", ch[keymode], number.val);
  if(number.has > 0) t = drawer_idbyname(code);
  else if(number.has < 0) t = allid[keymode];
  else t = (keymode == KEYGEOM) ? WORLDGEOM
    : FOCUSID;
  number = onum;
  onum.has = onum.expon = 0;
  keymode = KEYNONE;
  return t;
}

gxacol (gaint clr, gaint red, gaint green, gaint blue ) {
gaint rtn;
  rtn=1;
  hout4i(-5,clr,red,green,blue);
  if (intflg) rtn = gxdacl (clr, red, green, blue);
  if (clr>15 && clr<=255) {
    reds[clr] = red;
    grns[clr] = green;
    blus[clr] = blue;
  }
  return rtn;
}

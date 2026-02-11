teepal1() {
  Layer **l, *ll;
  int p, i, j;
  static char *tp;
  static char gonv[1024];
  if (!gonv[1023]) {
    for (i=1; i<1024; i++) gonv[i]=pow(i*(1/1023.), .5)*255.4;
  }
  for (tp=paljetti, i=0; i<256; i++) {
    Argb *c=pal_getcol(kb_data.pal, i);
    float r=c->r*con+bri, g=c->g*con+bri, b=c->b*con+bri;
    *tp++=gonv[r<0?0:r>1?1023:(int)(r*1023.4)];
    *tp++=gonv[g<0?0:g>1?1023:(int)(g*1023.4)];
    *tp++=gonv[b<0?0:b>1?1023:(int)(b*1023.4)];
  }
  return paljetti;
}

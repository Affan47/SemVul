HLStoRGB(float h, float l, float s, float *r, float *g, float *b)


{
  float m2, m1;

  if (h < 0.0)   h = h + ((int)(-h/360)+1)*  360.0;
  if (h > 360.0) h = h - ((int)( h/360))  *  360.0;

  if (l <= 0.5)
     m2 = l*(1.0 + s);
  else
     m2 = l + s - l*s;
  m1 = 2.0*l - m2;
  if (s == 0.0) {
     *r = l;
     *g = l;
     *b = l;
  }
  else {
     *r = ValueFcn(m1,m2, h + 120.0);
     *g = ValueFcn(m1, m2, h);
     *b = ValueFcn(m1, m2, h - 120.0);
  }
  return OK;
}

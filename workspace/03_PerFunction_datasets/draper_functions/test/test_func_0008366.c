step(double s) {
  if (s < 0) s = -s;
  A = rint(s);
  B = 1;
  while (fabs(s-A/B) > epsilon && B<=(0x7fffffff/10)) {B *= 10; A = rint(s*B);}
}

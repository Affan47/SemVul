clicyc (gaint *ti) {
  if (pfi->climo>0) {
    while (*ti>pfi->cysiz-1) *ti = *ti - pfi->cysiz;
    while (*ti<0) *ti = *ti + pfi->cysiz;
  }
}

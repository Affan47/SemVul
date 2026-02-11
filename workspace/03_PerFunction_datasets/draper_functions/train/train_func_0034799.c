sect4spp (unsigned char *s4, struct gag2 *pg2, gaint pos1, gaint *pp2) {
gaint sp1,sp2;
  sp1 = sp2 = -999;
  sp1 = gagby(s4,pos1+0,1);
  sp2 = gagby(s4,pos1+1,1);
  printf("  PDT=%d Spatial ",pg2->pdt);
  if (sp1<=255) CodeTable4p10(sp1);
  printf(", ");
  if (sp2<=255) CodeTable4p15(sp2);
  printf(" \n");
  *pp2 = sp2;
  return (sp1);
}

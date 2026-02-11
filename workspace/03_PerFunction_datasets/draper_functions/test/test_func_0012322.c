ltranslate(int *codon, gene *t, csw *sw)
{ int code,p1,p2,p3;
  if (t->genetype == CDS) code = t->asst;
  else code = sw->geneticcode;
  if ((p1 = *codon) >= AMBIG) return(ambig_aaname[0]);
  if ((p2 = codon[1]) >= AMBIG) return(ambig_aaname[0]);
  if ((p3 = codon[2]) >= AMBIG) return(ambig_aaname[0]);
  return(aaletter[aamap[code][((3-p3)<<4)+((3-p2)<<2)+(3-p1)]]); }

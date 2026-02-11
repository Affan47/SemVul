ptranslate(int *codon, csw *sw)
{ int p1,p2,p3;
  if ((p1 = *codon) >= AMBIG) return(ambig_aaname[0]);
  if ((p2 = codon[1]) >= AMBIG) return(ambig_aaname[0]);
  if ((p3 = codon[2]) >= AMBIG) return(ambig_aaname[0]);
  return(aapolarity[aamap[sw->geneticcode][((3-p3)<<4)+((3-p2)<<2)+(3-p1)]]); }

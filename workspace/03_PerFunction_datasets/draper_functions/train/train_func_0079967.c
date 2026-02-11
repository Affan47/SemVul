translate(int *codon, csw *sw)
{ int p1,p2,p3,aa;
  if ((p1 = *codon) >= AMBIG) return(ambig_aaname);
  if ((p2 = codon[1]) >= AMBIG) return(ambig_aaname);
  if ((p3 = codon[2]) >= AMBIG) return(ambig_aaname);
  aa = aamap[sw->geneticcode][((3-p3)<<4)+((3-p2)<<2)+(3-p1)];
  if ((aa == SeC) || (aa == Pyl)) aa = Stop;
  return(aaname[aa]); }

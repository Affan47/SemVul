ichainMatch(GffObj* t, GffObj* r, bool& exonMatch, int fuzz=0) {


  exonMatch=false;
  int imax=r->exons.Count()-1;
  int jmax=t->exons.Count()-1;
  if (imax==0 || jmax==0) {
     if (imax!=jmax) return false;
     exonMatch=r->exons[0]->coordMatch(t->exons[0],fuzz);


     return exonMatch;
     }

  if (r->exons[imax]->start<t->exons[0]->end ||
      t->exons[jmax]->start<r->exons[0]->end )
          {
           return false;
          }

  int i=1;
  int j=1;
  bool exmism=false;
  while (i<=imax && j<=jmax) {
     uint rstart=r->exons[i-1]->end;
     uint rend=r->exons[i]->start;
     uint tstart=t->exons[j-1]->end;
     uint tend=t->exons[j]->start;
     if (tend<rstart) { j++; continue; }
     if (rend<tstart) { i++; continue; }
     break;
     }
  if (i>1 || i>imax || j>jmax) {


      return false;
      }

  if (i!=j || imax!=jmax) {
      exmism=true;


      if (jmax<imax) return false;
      if (fuzz==0) return false;
      }
  for (;i<=imax && j<=jmax;i++,j++) {
    if (abs((int)(r->exons[i-1]->end-t->exons[j-1]->end))>fuzz ||
        abs((int)(r->exons[i]->start-t->exons[j]->start))>fuzz) {
        return false;
        }
    }

  if (!exmism) {

          exonMatch = ( abs((int)(r->exons[0]->start-t->exons[0]->start))<=fuzz &&
               abs((int)(r->exons[imax]->end-t->exons[jmax]->end))<=fuzz );
          }

  return true;
}

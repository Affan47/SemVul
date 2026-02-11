intronRedundant(GffObj& ti, GffObj&  tj) {


 int imax=ti.exons.Count()-1;
 int jmax=tj.exons.Count()-1;
 if (imax==0 || jmax==0) return false;
 if (ti.exons[imax]->start<tj.exons[0]->end ||
     tj.exons[jmax]->start<ti.exons[0]->end )
         return false;

 uint eistart=0, eiend=0, ejstart=0, ejend=0;
 int i=1;
 int j=1;

 while (i<=imax && j<=jmax) {
    eistart=ti.exons[i-1]->end;
    eiend=ti.exons[i]->start;
    ejstart=tj.exons[j-1]->end;
    ejend=tj.exons[j]->start;
    if (ejend<eistart) { j++; continue; }
    if (eiend<ejstart) { i++; continue; }

    break;
    }
 if ((i>1 && j>1) || i>imax || j>jmax) {
     return false;

     }
 if (eistart!=ejstart || eiend!=ejend) return false;

 if (j>i) {

   if (ti.start<tj.exons[j-1]->start) return false;


   if (ti.exons[imax]->start>tj.exons[jmax]->start) return false;

   }
  else if (i>j) {

   if (tj.start<ti.exons[i-1]->start) return false;


   if (tj.exons[jmax]->start>ti.exons[imax]->start) return false;

   }

 i++;
 j++;
 while (i<=imax && j<=jmax) {
  if (ti.exons[i-1]->end!=tj.exons[j-1]->end ||
      ti.exons[i]->start!=tj.exons[j]->start) return false;
  i++;
  j++;
  }
 i--;
 j--;
 if (i==imax && j<jmax) {

   if (ti.end>tj.exons[j]->end) return false;
   }
 else if (j==jmax && i<imax) {
   if (tj.end>ti.exons[i]->end) return false;
   }
 return true;
}

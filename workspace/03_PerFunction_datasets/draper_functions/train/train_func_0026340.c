betterRef(GffObj* a, GffObj* b) {
 if (a==NULL || b==NULL) return (a!=NULL);
 if (a->exons.Count()!=b->exons.Count()) return (a->exons.Count()>b->exons.Count());
 if (a->hasCDS() && !b->hasCDS())
        return true;
   else {
     if (b->hasCDS() && !a->hasCDS()) return false;
     return (a->covlen>b->covlen);
     }
 }

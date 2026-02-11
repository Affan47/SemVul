inPolyRun(char strand, GffObj& m, GList<GLocus>* rloci, int& rlocidx) {

 if (rloci==NULL || rloci->Count()==0) return false;
  if (strand=='-') {
        rlocidx=qsearch_loci(m.end, *rloci);


        GLocus* rloc=NULL;
        if (rlocidx<0) return false;
        while (rlocidx<rloci->Count()) {
           rloc=rloci->Get(rlocidx);
           if (rloc->start>m.end+polyrun_range) break;
           if (rloc->start+6>m.end) return true;
           rlocidx++;
           }
        }
      else {
        rlocidx=qsearch_loci(m.end, *rloci);
        GLocus* rloc=NULL;


        if (rlocidx<0) rlocidx=rloci->Count();
        while ((--rlocidx)>=0) {
          rloc=rloci->Get(rlocidx);
          if (m.start>rloc->start+GFF_MAX_LOCUS) break;
          if (m.start+6>rloc->end && m.start<rloc->end+polyrun_range) return true;
          }
        }
  return false;
}

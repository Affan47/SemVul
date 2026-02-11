addCloseExtensions ( vector<CloseLegPtr> &targetcloselegs, int number ) {
  if ( fm::closelegsoccsused ) {
    for ( int i = 1; i < (int) fm::candidatecloselegsoccs.size (); i++ )
      if ( fm::candidatecloselegsoccsused[i] ) {
        vector<CloseLegOccurrences> &edgelabeloccs = fm::candidatecloselegsoccs[i];
        for ( EdgeLabel j = 0; j < edgelabeloccs.size (); j++ ) {
          if ( edgelabeloccs[j].frequency >= fm::minfreq ) {
            CloseLegPtr closelegptr = new CloseLeg;
            closelegptr->tuple.label = j;
            closelegptr->tuple.to = i;
            closelegptr->tuple.from = number;
            swap ( closelegptr->occurrences, edgelabeloccs[j] );
            targetcloselegs.push_back ( closelegptr );
          }
        }
      }
  }
}

buildDeltaList(
   PermGroup *G,
   UnsignedS *DeltaList[])
{
   Unsigned  d, i, listLen, basePt;
   for ( d = 1 ; d <= G->baseSize ; ++d)  {
      listLen = 0;
      basePt = G->base[d];
      for ( i = 1 ; i <= d ; ++i )
         if ( G->schreierVec[i][basePt] )
            DeltaList[d][++listLen] = i;
      DeltaList[d][++listLen] = 0;
   }
}

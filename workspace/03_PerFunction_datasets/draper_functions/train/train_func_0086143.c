perform(LoopInfo *LI) {
  LoopBlocksTraversal Traversal(*this, LI);
  for (LoopBlocksTraversal::POTIterator POI = Traversal.begin(),
         POE = Traversal.end(); POI != POE; ++POI) ;
}

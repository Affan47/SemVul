doinit() {
  addVertex(WSFSFVertex_);
  addVertex(NFSFVertex_);
  addVertex(GFSFVertex_);
  addVertex(HSFSFVertex_);
  addVertex(CFSFVertex_);
  addVertex(GSFSFVertex_);
  addVertex(GGSQSQVertex_);
  addVertex(GSGSGVertex_);
  addVertex(NNZVertex_);
  if(NNPVertex_) addVertex(NNPVertex_);
  if(GNGVertex_) addVertex(GNGVertex_);
  addVertex(CCZVertex_);
  addVertex(CNWVertex_);
  addVertex(GOGOHVertex_);
  addVertex(WHHVertex_);
  addVertex(NCTVertex_);
  if(gravitino_) {
    if(GVNHVertex_) addVertex(GVNHVertex_);
    if(GVNVVertex_) addVertex(GVNVVertex_);
    if(GVFSVertex_) addVertex(GVFSVertex_);
  }
  BSMModel::doinit();
}

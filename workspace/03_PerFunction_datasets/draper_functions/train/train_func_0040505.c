doinit() {
  if(runningMass_) {
    runningMass_->init();
  }

  addVertex(vertexFFZ());
  addVertex(vertexFFP());
  addVertex(vertexFFG());
  addVertex(vertexFFW());
  addVertex(vertexFFH());
  addVertex(vertexWWH());
  addVertex(GGGVertex_);
  addVertex(WWWVertex_);
  addVertex(GGGGVertex_);
  addVertex(WWWWVertex_);
  addVertex(vertexHGG());
  addVertex(HPPVertex_);
  if(HHHVertex_ ) addVertex(HHHVertex_);
  if(WWHHVertex_) addVertex(WWHHVertex_);
  StandardModelBase::doinit();
}

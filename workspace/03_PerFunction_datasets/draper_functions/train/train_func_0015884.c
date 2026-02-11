updateFinalStateShowerProduct(ShowerProgenitorPtr progenitor,
					       ShowerParticlePtr parent,
					       const ShowerParticleVector & children) {
  assert(children.size()==2);
  bool matches[2];
  for(unsigned int ix=0;ix<2;++ix) {
    matches[ix] = children[ix]->id()==progenitor->id();
  }
  ShowerParticlePtr newpart;
  if(matches[0]&&matches[1]) {
    if(parent->showerKinematics()->z()>0.5) newpart=children[0];
    else                                    newpart=children[1];
  }
  else if(matches[0]) newpart=children[0];
  else if(matches[1]) newpart=children[1];
  _outgoingLines[progenitor]=newpart;
}

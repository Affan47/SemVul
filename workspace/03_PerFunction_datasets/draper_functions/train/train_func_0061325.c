updateParent(const tShowerParticlePtr parent,
						 const ShowerParticleVector & children,
						 bool) const {
  IdList ids(3);
  ids[0] = parent->id();
  ids[1] = children[0]->id();
  ids[2] = children[1]->id();
  vector<Energy> virtualMasses = SudakovFormFactor()->virtualMasses(ids);
  if(children[0]->children().empty()) children[0]->setVirtualMass(virtualMasses[1]);
  if(children[1]->children().empty()) children[1]->setVirtualMass(virtualMasses[2]);

  Energy2 pt2=sqr(z()*(1.-z()))*sqr(scale())
    - sqr(children[0]->virtualMass())*(1.-z())
    - sqr(children[1]->virtualMass())*    z() ;
  if(ids[0]!=ParticleID::g) pt2 += z()*(1.-z())*sqr(virtualMasses[0]);
  Energy2 q2 =
    sqr(children[0]->virtualMass())/z() +
    sqr(children[1]->virtualMass())/(1.-z()) +
    pt2/z()/(1.-z());
  if(pt2<ZERO) {
    parent->setVirtualMass(ZERO);
  }
  else {
    parent->setVirtualMass(sqrt(q2));
    pT(sqrt(pt2));
  }
}

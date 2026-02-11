spaceLikeDecayShower(tShowerParticlePtr particle,
				   Energy maxscale,
				   Energy minmass,ShowerInteraction::Type type) {

  double reduction = getReductionFactor(particle);
  Branching fb;
  while (true) {
    fb=_splittingGenerator->chooseDecayBranching(*particle,maxscale,minmass,
						 reduction*_initialenhance,type);

    if(!fb.kinematics) return false;

    if(!spaceLikeDecayVetoed(fb,particle)) break;

    particle->setEvolutionScale(fb.kinematics->scale());
  }


  particle->setShowerKinematics(fb.kinematics);


  tcPDPtr pdata[2];
  for(unsigned int ix=0;ix<2;++ix) pdata[ix]=getParticleData(fb.ids[ix+1]);
  if(particle->id()!=fb.ids[0]) {
    for(unsigned int ix=0;ix<2;++ix) {
      tPDPtr cc(pdata[ix]->CC());
      if(cc) pdata[ix]=cc;
    }
  }
  ShowerParticleVector theChildren;
  theChildren.push_back(new_ptr(ShowerParticle(pdata[0],true)));
  theChildren.push_back(new_ptr(ShowerParticle(pdata[1],true)));

  particle->showerKinematics()->updateChildren(particle, theChildren,true);


  _currenttree->updateInitialStateShowerProduct(_progenitor,theChildren[0]);
  _currenttree->addInitialStateBranching(particle,theChildren[0],theChildren[1]);

  spaceLikeDecayShower(theChildren[0],maxscale,minmass,type);

  timeLikeShower(theChildren[1],type,true);

  return true;
}

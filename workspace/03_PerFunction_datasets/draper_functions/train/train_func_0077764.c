initialize(const IdList & ids, Energy2 & tmin,const bool cc) {
  ids_=ids;
  if(cc) {
    for(unsigned int ix=0;ix<ids.size();++ix) {
      if(getParticleData(ids[ix])->CC()) ids_[ix]*=-1;
    }
  }
  tmin = cutOffOption() != 2 ? ZERO : 4.*pT2min();
  masses_ = virtualMasses(ids);
  masssquared_.clear();
  for(unsigned int ix=0;ix<masses_.size();++ix) {
    masssquared_.push_back(sqr(masses_[ix]));
    if(ix>0) tmin=max(masssquared_[ix],tmin);
  }
}

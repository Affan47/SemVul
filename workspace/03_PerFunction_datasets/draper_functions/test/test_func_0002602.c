debug(double me2) const {
  if( !generator()->logfile().is_open() ) return;
  long id1 = mePartonData()[0]->id();
  long id2 = mePartonData()[1]->id();
  long id4 = mePartonData()[3]->id();
  if(id1 != ParticleID::g || id2 != ParticleID::g ||
     id4 != ParticleID::g ) return;
  unsigned int iloc(0);
  for(;iloc<vector_.size();++iloc)
    if(vector_[iloc].first) break;
  double gs = abs(vector_[iloc].second->norm());
  InvEnergy kappa = abs(vector_[iloc].first->norm())*UnitRemoval::InvE;
  Energy2 mg2 = sqr(meMomenta()[2].mass());
  double anal2 = 3./32.*sqr(gs)*sqr(kappa)/sHat()/tHat()/uHat()
    *(pow<4,1>(sHat()-mg2)+pow<4,1>(tHat()-mg2)+pow<4,1>(uHat()-mg2));
  double diff = abs((anal2 - me2)/(anal2+me2));
  if( diff > 1e-4 ) {
    generator()->log()
      << mePartonData()[0]->PDGName() << ","
      << mePartonData()[1]->PDGName() << "->"
      << mePartonData()[2]->PDGName() << ","
      << mePartonData()[3]->PDGName() << "   difference: "
      << setprecision(10) << diff << "  ratio: " << anal2/me2
      << '\n';
  }
}

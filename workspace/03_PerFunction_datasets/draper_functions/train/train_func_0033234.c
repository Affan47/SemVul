me2() const {

  double me(0.);

  if(mePartonData()[0]->id()==ParticleID::g) {
    VectorWaveFunction      g1w(meMomenta()[0],mePartonData()[0],incoming);
    VectorWaveFunction      g2w(meMomenta()[1],mePartonData()[1],incoming);
    SpinorBarWaveFunction    qw(meMomenta()[2],mePartonData()[2],outgoing);
    SpinorWaveFunction    qbarw(meMomenta()[3],mePartonData()[3],outgoing);
    ScalarWaveFunction    higgs(meMomenta()[4],mePartonData()[4],1.,outgoing);
    vector<VectorWaveFunction> g1,g2;
    vector<SpinorBarWaveFunction> q;
    vector<SpinorWaveFunction> qbar;
    for(unsigned int ix=0;ix<2;++ix) {
      g1w.reset(2*ix);g1.push_back(g1w);
      g2w.reset(2*ix);g2.push_back(g2w);
      qw.reset(ix);q.push_back(qw);
      qbarw.reset(ix);qbar.push_back(qbarw);
    }

    me=ggME(g1,g2,q,qbar,higgs,0);
  }

  else {
    SpinorWaveFunction    q1w(meMomenta()[0],mePartonData()[0],incoming);
    SpinorBarWaveFunction q2w(meMomenta()[1],mePartonData()[1],incoming);
    SpinorBarWaveFunction q3w(meMomenta()[2],mePartonData()[2],outgoing);
    SpinorWaveFunction    q4w(meMomenta()[3],mePartonData()[3],outgoing);
    ScalarWaveFunction    higgs(meMomenta()[4],mePartonData()[4],1.,outgoing);
    vector<SpinorWaveFunction>    q1,q4;
    vector<SpinorBarWaveFunction> q2,q3;
    for(unsigned int ix=0;ix<2;++ix) {
      q1w.reset(ix);q1.push_back(q1w);
      q2w.reset(ix);q2.push_back(q2w);
      q3w.reset(ix);q3.push_back(q3w);
      q4w.reset(ix);q4.push_back(q4w);
    }

    me = qqME(q1,q2,q3,q4,higgs,0);
  }
  return me*sHat()*UnitRemoval::InvE2;
}

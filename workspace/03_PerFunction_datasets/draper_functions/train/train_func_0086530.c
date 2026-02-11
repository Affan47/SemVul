getDiagrams() const {
  tcPDPtr gamma = getParticleData(ParticleID::gamma);
  for(int ix=1;ix<17;++ix) {

    if(ix==7) ix+=4;
    if(ix>11&&ix%2==0) ++ix;

    bool quark = ix<=6 && (process_==0 || process_==1 || process_-10==ix);

    bool lepton= ix>=11 && ix<=16 &&
      (process_==0 || process_==2 || ( (ix-9)/2 ==process_-4) );

    if(!quark && !lepton) continue;
    tcPDPtr lm = getParticleData(ix);
    tcPDPtr lp = lm->CC();

    add(new_ptr((Tree2toNDiagram(3),gamma,lp,gamma,1,lm, 2,lp,-1)));

    add(new_ptr((Tree2toNDiagram(3),gamma,lp,gamma,2,lm, 1,lp,-2)));
  }
}

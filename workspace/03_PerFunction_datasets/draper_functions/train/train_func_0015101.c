getDiagrams() const {

  bool gamma = _gammaZ==0 || _gammaZ==1;
  bool Z0    = _gammaZ==0 || _gammaZ==2;

  for ( int ix=1; ix<17; ++ix ) {

    if(ix==7) ix+=4;

    bool quark = ix<=6 && (_process==0 || _process==1 || _process-10==ix);

    bool lepton= ix>=11 && ix<=16
      && (_process==0
	  || _process==2
	  || (_process==3 && ix%2==1)
	  || (_process==4 && ix%2==0)
	  || (ix%2==0 && (ix-10)/2==_process-7)
	  || (ix%2==1 && (ix-9)/2 ==_process-4)
	  );

    if(!(quark||lepton)) continue;
    tcPDPtr lm = getParticleData(ix);
    tcPDPtr lp = lm->CC();
    for(int i = _minflavour; i <= _maxflavour; ++i) {
      tcPDPtr q  = getParticleData(i);
      tcPDPtr qb = q->CC();
      if(Z0)    add(new_ptr((Tree2toNDiagram(2), q, qb, 1, _z0   , 3, lm, 3, lp, -1)));
      if(gamma) add(new_ptr((Tree2toNDiagram(2), q, qb, 1, _gamma, 3, lm, 3, lp, -2)));
    }
  }
}

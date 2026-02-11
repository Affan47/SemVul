constructVertex(tSubProPtr sub) {
  ParticleVector ext = hardParticles(sub);

  VBVector v1, v2;
  VectorWaveFunction(v1, ext[0], incoming, false, true);
  VectorWaveFunction(v2, ext[1], incoming, false, true);


  bool mc  = !(ext[2]->momentum().mass() > ZERO);
  bool md  = !(ext[3]->data()    .mass() > ZERO);
  VBVector v4;
  vector<TensorWaveFunction> t3;
  TensorWaveFunction(t3, ext[2], outgoing, true, mc);
  VectorWaveFunction(v4, ext[3], outgoing, true, md);

  setRescaledMomenta(ext);

  VectorWaveFunction vr1(rescaledMomenta()[0],
 			 ext[0]->dataPtr(), incoming);
  VectorWaveFunction vr2(rescaledMomenta()[1],
			 ext[1]->dataPtr(), incoming);
  TensorWaveFunction tr3(rescaledMomenta()[2],
			 ext[2]->dataPtr(), outgoing);
  VectorWaveFunction vr4(rescaledMomenta()[3],
			 ext[3]->dataPtr(), outgoing);
  for( unsigned int ihel = 0; ihel < 2; ++ihel ) {
    vr1.reset(2*ihel);
    v1[ihel] = vr1;
    vr2.reset(2*ihel);
    v2[ihel] = vr2;
    tr3.reset(4*ihel);
    t3[4*ihel] = tr3;
    vr4.reset(2*ihel);
    v4[2*ihel] = vr4;
  }
  if( !md ) {
    vr4.reset(1);
    v4[1] = vr4;
  }
  if( !mc ) {
    for(unsigned int ihel=1;ihel<4;++ihel) {
      tr3.reset(ihel);
      t3[ihel] = tr3;
    }
  }
  double dummy(0.);
  ProductionMatrixElement pme = vv2tvHeME(v1, v2, t3, v4,dummy,false);
  createVertex(pme,ext);
}

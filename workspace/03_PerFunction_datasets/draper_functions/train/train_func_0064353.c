initProc() {


  mRes     = particleDataPtr->m0(42);
  GammaRes = particleDataPtr->mWidth(42);
  m2Res    = mRes*mRes;
  GamMRat  = GammaRes / mRes;


  kCoup    = settingsPtr->parm("LeptoQuark:kCoup");


  ParticleDataEntry* LQPtr = particleDataPtr->particleDataEntryPtr(42);
  idQuark  = LQPtr->channel(0).product(0);


  openFrac = particleDataPtr->resOpenFrac(42, -42);

}

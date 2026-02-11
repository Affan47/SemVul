ScalarVectorFormFactor(Energy2 q2, unsigned int mode,
						     int, int id1,
						     Energy, Energy,Complex & A0,
						     Complex & A1,Complex & A2,
						     Complex & V) const {
  useMe();
  double ratio(q2/sqr(_massV[mode])),ratioP(q2/sqr(_massP[mode]));
  A0= _A00[mode]/(1.-ratioP)/(1.-ratioP*(_sigma1A0[mode]-_sigma2A0[mode]*ratioP));
  A1= _A10[mode]            /(1.-ratio *(_sigma1A1[mode]-_sigma2A1[mode]*ratio));
  A2= _A20[mode]            /(1.-ratio *(_sigma1A2[mode]-_sigma2A2[mode]*ratio));
  V =-_V0[mode] /(1.-ratio )/(1.-ratio *(_sigma1V0[mode]-_sigma2V0[mode]*ratio ));
  int jspin,spect,inquark,outquark;
  formFactorInfo(mode,jspin,spect,inquark,outquark);
  if(abs(outquark)!=abs(spect)) return;
  if(abs(spect)>2) return;
  double fact(sqrt(0.5));
  if(id1==ParticleID::rho0&&abs(outquark)==1) fact=-fact;
  A0 *= fact;
  A1 *= fact;
  A2 *= fact;
  V  *= fact;
}

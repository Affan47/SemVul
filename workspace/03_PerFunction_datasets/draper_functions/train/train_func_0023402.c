Init() {

  static ClassDocumentation<LightBaryonQuarkModelFormFactor> documentation
    ("The LightBaryonQuarkModelFormFactor class implements"
     " the quark model calculation of hep-ph/9409272 for the form-factors"
     " for the light quarks",
     "The quark model calculation of \\cite{Schlumpf:1994fb} was used"
     "for the weak decay of the light baryons",
     "\\bibitem{Schlumpf:1994fb}\n"
     "F.~Schlumpf,\n"
     "Phys.\\ Rev.\\  D {\\bf 51} (1995) 2262 [arXiv:hep-ph/9409272].\n"
     "%%CITATION = PHRVA,D51,2262;%%\n");

  static ParVector<LightBaryonQuarkModelFormFactor,double> interfacef1
    ("f1",
     "The form-factor f1 at zero q^2",
     &LightBaryonQuarkModelFormFactor::_f1,
     0, 0, 0, -10., 10., false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,double> interfaceg1
    ("g1",
     "The form-factor g1 at zero q^2",
     &LightBaryonQuarkModelFormFactor::_g1,
     0, 0, 0, -10., 10., false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,InvEnergy> interfacef2
    ("f2",
     "The form-factor f2 at zero q^2",
     &LightBaryonQuarkModelFormFactor::_f2,
     1./GeV, 0, ZERO, -10./GeV, 10./GeV, false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,InvEnergy> interfaceg2
    ("g2",
     "The form-factor g2 at zero q^2",
     &LightBaryonQuarkModelFormFactor::_g2,
     1./GeV, 0, ZERO, -10./GeV, 10./GeV, false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,Energy> interfaceLambdaf1
    ("Lambdaf1",
     "The first mass for the energy dependence of the f1 form-factor.",
     &LightBaryonQuarkModelFormFactor::_Lambdaf1,
     1.*GeV, 0, ZERO, -10.*GeV, 10.*GeV, false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,Energy> interfaceLambdaf2
    ("Lambdaf2",
     "The second mass for the energy dependence of the f1 form-factor.",
     &LightBaryonQuarkModelFormFactor::_Lambdaf2,
     1.*GeV, 0, ZERO, -10.*GeV, 10.*GeV, false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,Energy> interfaceLambdag1
    ("Lambdag1",
     "The first mass for the energy dependence of the g1 form-factor.",
     &LightBaryonQuarkModelFormFactor::_Lambdag1,
     1.*GeV, 0, ZERO, -10.*GeV, 10.*GeV, false, false, true);

  static ParVector<LightBaryonQuarkModelFormFactor,Energy> interfaceLambdag2
    ("Lambdag2",
     "The second mass for the energy dependence of the g1 form-factor.",
     &LightBaryonQuarkModelFormFactor::_Lambdag2,
     1.*GeV, 0, ZERO, -10.*GeV, 10.*GeV, false, false, true);
}

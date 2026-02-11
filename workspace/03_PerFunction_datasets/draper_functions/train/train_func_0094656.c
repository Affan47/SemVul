Init() {

  static ClassDocumentation<SingletonFormFactor> documentation
    ("The SingletonFormFactor class implements the"
     " form-factors of PRD43, 2939 for the decay of spin-1/2 baryons"
     " containing one heavy quark.",
     "Spin-1/2 baryons with one heavy quark were decayed using "
     "the form factors in \\cite{Singleton:1990ye}.",
     "%\\cite{Singleton:1990ye}\n"
     "\\bibitem{Singleton:1990ye}\n"
     "  R.~L.~Singleton,\n"
     "  %``Semileptonic baryon decays with a heavy quark,''\n"
     "  Phys.\\ Rev.\\  D {\\bf 43} (1991) 2939.\n"
     "  %%CITATION = PHRVA,D43,2939;%%\n"
     );

  static Parameter<SingletonFormFactor,Energy> interfaceCharmMass
    ("CharmMass",
     "The mass of the charm quark",
     &SingletonFormFactor::_mcharm, GeV, 1.8*GeV, ZERO, 10.0*GeV,
     false, false, true);

  static Parameter<SingletonFormFactor,Energy> interfaceStrangeMass
    ("StrangeMass",
     "The mass of the strange quark",
     &SingletonFormFactor::_mstrange, GeV, 0.51*GeV, ZERO, 10.0*GeV,
     false, false, true);

  static Parameter<SingletonFormFactor,double> interfaceThetaLambda
    ("ThetaLambda",
     "The mixing angle for the Lambda",
     &SingletonFormFactor::_thetalambda, 0.785398163, 0.0, 6.28318507,
     false, false, true);

  static Parameter<SingletonFormFactor,double> interfaceThetaSigma
    ("ThetaSigma",
     "The mixing angle for the Sigma",
     &SingletonFormFactor::_thetasigma, 0.785398163, 0.0, 6.28318507,
     false, false, true);

  static Parameter<SingletonFormFactor,double> interfaceThetaXi
    ("ThetaXi",
     "The mixing angle for the Xi",
     &SingletonFormFactor::_thetaxi, 0.785398163, 0.0, 6.28318507,
     false, false, true);

  static Parameter<SingletonFormFactor,double> interfaceThetaXiPrime
    ("ThetaXiPrime",
     "The mixing angle for the Xi'",
     &SingletonFormFactor::_thetaxip, 0.785398163, 0.0, 6.28318507,
     false, false, true);

  static ParVector<SingletonFormFactor,Energy> interfacePoleMass
    ("PoleMass",
     "The mass for the energy dependence of the form-factors.",
     &SingletonFormFactor::_polemass,
     1.*GeV, 0, ZERO, -10.*GeV, 10.*GeV, false, false, true);
}

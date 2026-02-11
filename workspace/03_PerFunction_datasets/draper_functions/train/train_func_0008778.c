Init() {

  static ClassDocumentation<DrellYanBase> documentation
    ("The DrellYanBase class provides a base class for the"
     " corrections to Drell-Yan type processes");

  static Parameter<DrellYanBase,double> interfaceQQbarChannelWeight
    ("QQbarChannelWeight",
     "The relative weights of the q qbar abd q g channels for selection."
     " This is a technical parameter for the phase-space generation and "
     "should not affect the results only the efficiency and fraction"
     " of events with weight > 1.",
     &DrellYanBase::_channelwgtA, 0.12, 0.01, 100.,
     false, false, Interface::limited);

  static Parameter<DrellYanBase,double> interfaceQGChannelWeight
    ("QGChannelWeight",
     "The relative weights of the qg abd qbar g channels for selection."
     " This is a technical parameter for the phase-space generation and "
     "should not affect the results only the efficiency and fraction",
     &DrellYanBase::_channelwgtB, 2., 0.01, 100.,
     false, false, Interface::limited);

  static Reference<DrellYanBase,ShowerAlpha> interfaceCoupling
    ("Coupling",
     "Pointer to the object to calculate the coupling for the correction",
     &DrellYanBase::_alpha, false, false, true, false, false);

  static Parameter<DrellYanBase,double> interfacePower
    ("Power",
     "The power for the sampling of the matrix elements",
     &DrellYanBase::_power, 2.0, 1.0, 10.0,
     false, false, Interface::limited);

  static Parameter<DrellYanBase,double> interfacePrefactorqqbar
    ("Prefactorqqbar",
     "The prefactor for the sampling of the q qbar channel",
     &DrellYanBase::_preqqbar, 5.0, 0.0, 1000.0,
     false, false, Interface::limited);

  static Parameter<DrellYanBase,double> interfacePrefactorqg
    ("Prefactorqg",
     "The prefactor for the sampling of the q g channel",
     &DrellYanBase::_preqg, 3.0, 0.0, 1000.0,
     false, false, Interface::limited);

  static Parameter<DrellYanBase,double> interfacePrefactorgqbar
    ("Prefactorgqbar",
     "The prefactor for the sampling of the g qbar channel",
     &DrellYanBase::_pregqbar, 3.0, 0.0, 1000.0,
     false, false, Interface::limited);

  static Parameter<DrellYanBase, Energy> interfacePtMin
    ("minPt",
     "The pt cut on hardest emision generation"
     "2*(1-Beta)*exp(-sqr(intrinsicpT/RMS))/sqr(RMS)",
     &DrellYanBase::_min_pt, GeV, 2.*GeV, ZERO, 100000.0*GeV,
     false, false, Interface::limited);
}

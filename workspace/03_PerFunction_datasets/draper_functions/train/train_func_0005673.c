Init() {

  static ClassDocumentation<BtoSGammaDecayer> documentation
    ("The BtoSGammaDecayer class performs to the exclusive decay B to s gamma");

  static Reference<BtoSGammaDecayer,BtoSGammaHadronicMass> interfaceHadronicMass
    ("HadronicMass",
     "Pointer to the object computing the hadronic mass spectrum.",
     &BtoSGammaDecayer::_hadronicmass, false, false, true, false, false);

}

Init() {

  static RefVector<DecayPhaseSpaceChannel,ParticleData> interfaceIntermediateParticles
    ("IntermediateParticles",
     "The intermediate particles in the decay chain.",
     &DecayPhaseSpaceChannel::_intpart, 0, false, false, true, false);

  static ParVector<DecayPhaseSpaceChannel,int> interfacejactype
    ("Jacobian",
     "The type of Jacobian to use for the intermediate particle",
     &DecayPhaseSpaceChannel::_jactype,
     0, 0, 0, 0, 1, false, false, true);

  static ParVector<DecayPhaseSpaceChannel,double> interfaceIntermediatePower
    ("IntermediatePower",
     "The power to use in the Jacobian",
     &DecayPhaseSpaceChannel::_intpower,
     0, 0, 0, -10, 10, false, false, true);

  static ParVector<DecayPhaseSpaceChannel,int> interfaceIntermediateDau1
    ("IntermediateDaughter1",
     "First Daughter of the intermediate",
     &DecayPhaseSpaceChannel::_intdau1,
     0, 0, 0, -10, 10, false, false, true);

  static ParVector<DecayPhaseSpaceChannel,int> interfaceIntermediateDau2
    ("IntermediateDaughter2",
     "Second Daughter of the intermediate",
     &DecayPhaseSpaceChannel::_intdau2,
     0, 0, 0, -10, 10, false, false, true);

  static ClassDocumentation<DecayPhaseSpaceChannel> documentation
    ("The DecayPhaseSpaceChannel class defines a channel"
     " for the multichannel integration of the phase space for a decay.");

}

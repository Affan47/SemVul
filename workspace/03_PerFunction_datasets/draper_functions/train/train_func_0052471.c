Init() {

  static ClassDocumentation<MEPP2HiggsJet> documentation
    ("The MEPP2HiggsJet class implements the matrix elements for"
     " Higgs+Jet production in hadron-hadron collisions.",
     "The theoretical calculations of \\cite{Baur:1989cm} and \\cite{Ellis:1987xu}"
     " were used for the Higgs+jet matrix element in hadron-hadron collisions.",
     "\\bibitem{Baur:1989cm} U.~Baur and E.~W.~N.~Glover,"
     "Nucl.\\ Phys.\\ B {\\bf 339} (1990) 38.\n"
     "\\bibitem{Ellis:1987xu} R.~K.~Ellis, I.~Hinchliffe, M.~Soldate and "
     "J.~J.~van der Bij, Nucl.\\ Phys.\\ B {\\bf 297} (1988) 221.");

  static Parameter<MEPP2HiggsJet,unsigned int> interfaceMaximumFlavour
    ("MaximumFlavour",
     "The maximum flavour of the quarks in the process",
     &MEPP2HiggsJet::_maxflavour, 5, 1, 5,
     false, false, Interface::limited);

  static Switch<MEPP2HiggsJet,unsigned int> interfaceShapeOption
    ("ShapeScheme",
     "Option for the treatment of the Higgs resonance shape",
     &MEPP2HiggsJet::_shapeopt, 1, false, false);
  static SwitchOption interfaceStandardShapeFixed
    (interfaceShapeOption,
     "FixedBreitWigner",
     "Breit-Wigner s-channel resonanse",
     1);
  static SwitchOption interfaceStandardShapeRunning
    (interfaceShapeOption,
     "MassGenerator",
     "Use the mass generator to give the shape",
     2);

  static Switch<MEPP2HiggsJet,unsigned int> interfaceProcess
    ("Process",
     "Which subprocesses to include",
     &MEPP2HiggsJet::_process, 0, false, false);
  static SwitchOption interfaceProcessAll
    (interfaceProcess,
     "All",
     "Include all subprocesses",
     0);
  static SwitchOption interfaceProcess1
    (interfaceProcess,
     "qqbar",
     "Only include the incoming q qbar subprocess",
     1);
  static SwitchOption interfaceProcessqg
    (interfaceProcess,
     "qg",
     "Only include the incoming qg subprocess",
     2);
  static SwitchOption interfaceProcessqbarg
    (interfaceProcess,
     "qbarg",
     "Only include the incoming qbar g subprocess",
     3);
  static SwitchOption interfaceProcessgg
    (interfaceProcess,
     "gg",
     "Only include the incoming gg subprocess",
     4);

  static Parameter<MEPP2HiggsJet,int> interfaceMinimumInLoop
    ("MinimumInLoop",
     "The minimum flavour of the quarks to include in the loops",
     &MEPP2HiggsJet::_minloop, 6, 4, 6,
     false, false, Interface::limited);

  static Parameter<MEPP2HiggsJet,int> interfaceMaximumInLoop
    ("MaximumInLoop",
     "The maximum flavour of the quarks to include in the loops",
     &MEPP2HiggsJet::_maxloop, 6, 4, 6,
     false, false, Interface::limited);

  static Switch<MEPP2HiggsJet,unsigned int> interfaceMassOption
    ("MassOption",
     "Option for the treatment of the masses in the loop diagrams",
     &MEPP2HiggsJet::_massopt, 0, false, false);
  static SwitchOption interfaceMassOptionFull
    (interfaceMassOption,
     "Full",
     "Include the full mass dependence",
     0);
  static SwitchOption interfaceMassOptionLarge
    (interfaceMassOption,
     "Large",
     "Use the heavy mass limit",
     1);

}

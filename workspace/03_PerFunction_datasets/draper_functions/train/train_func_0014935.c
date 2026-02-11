Init() {

  static ClassDocumentation<SubtractionDipole> documentation
    ("SubtractionDipole represents a dipole subtraction "
     "term in the formalism of Catani and Seymour.");

  static Reference<SubtractionDipole,MatchboxMEBase> interfaceUnderlyingBornME
    ("UnderlyingBornME",
     "The underlying Born matrix element.",
     &SubtractionDipole::theUnderlyingBornME, false, false, true, true, false);

  static Reference<SubtractionDipole,MatchboxMEBase> interfaceRealEmissionME
    ("RealEmissionME",
     "The real emission matrix element.",
     &SubtractionDipole::theRealEmissionME, false, false, true, true, false);


  static Reference<SubtractionDipole,TildeKinematics> interfaceTildeKinematics
    ("TildeKinematics",
     "Set the TildeKinematics object to be used.",
     &SubtractionDipole::theTildeKinematics, false, false, true, false, false);

  static Reference<SubtractionDipole,InvertedTildeKinematics> interfaceInvertedTildeKinematics
    ("InvertedTildeKinematics",
     "Set the InvertedTildeKinematics object to be used.",
     &SubtractionDipole::theInvertedTildeKinematics, false, false, true, true, false);

  static RefVector<SubtractionDipole,MatchboxReweightBase> interfaceReweights
    ("Reweights",
     "Reweight objects to be applied to this matrix element.",
     &SubtractionDipole::theReweights, -1, false, false, true, true, false);

}

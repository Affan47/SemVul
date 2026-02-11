Init() {

  static ClassDocumentation<SplittingGenerator> documentation
    ("There class is responsible for initializing the Sudakov form factors ",
     "and generating splittings.");

  static Switch<SplittingGenerator, bool> interfaceISRMode
    ("ISR",
     "Include initial-state radiation?",
     &SplittingGenerator::_isr_Mode, 1, false, false);
  static SwitchOption interfaceISRMode0
    (interfaceISRMode,"No","ISR (Initial State Radiation) is OFF", 0);
  static SwitchOption interfaceISRMode1
    (interfaceISRMode,"Yes","ISR (Initial State Radiation) is ON", 1);

  static Switch<SplittingGenerator, bool> interfaceFSRMode
    ("FSR",
     "Include final-state radiation?",
     &SplittingGenerator::_fsr_Mode, 1, false, false);
  static SwitchOption interfaceFSRMode0
    (interfaceFSRMode,"No","FSR (Final State Radiation) is OFF", 0);
  static SwitchOption interfaceFSRMode1
    (interfaceFSRMode,"Yes","FSR (Final State Radiation) is ON", 1);

  static Command<SplittingGenerator> interfaceAddSplitting
    ("AddFinalSplitting",
     "Adds another splitting to the list of splittings considered "
     "in the shower. Command is a->b,c; Sudakov",
     &SplittingGenerator::addFinalSplitting);

  static Command<SplittingGenerator> interfaceAddInitialSplitting
    ("AddInitialSplitting",
     "Adds another splitting to the list of initial splittings to consider "
     "in the shower. Command is a->b,c; Sudakov. Here the particle a is the "
     "particle that is PRODUCED by the splitting. b is the initial state "
     "particle that is splitting in the shower.",
     &SplittingGenerator::addInitialSplitting);

  static Command<SplittingGenerator> interfaceDeleteSplitting
    ("DeleteFinalSplitting",
     "Deletes a splitting from the list of splittings considered "
     "in the shower. Command is a->b,c; Sudakov",
     &SplittingGenerator::deleteFinalSplitting);

  static Command<SplittingGenerator> interfaceDeleteInitialSplitting
    ("DeleteInitialSplitting",
     "Deletes a splitting from the list of initial splittings to consider "
     "in the shower. Command is a->b,c; Sudakov. Here the particle a is the "
     "particle that is PRODUCED by the splitting. b is the initial state "
     "particle that is splitting in the shower.",
     &SplittingGenerator::deleteInitialSplitting);
}

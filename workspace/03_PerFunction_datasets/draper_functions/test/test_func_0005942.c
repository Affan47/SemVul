Init() {

  static ClassDocumentation<HardProcessConstructor> documentation
    ("Base class for implementation of the automatic generation of hard processes");

  static Switch<HardProcessConstructor,bool> interfaceDebugME
    ("DebugME",
     "Print comparison with analytical ME",
     &HardProcessConstructor::debug_, false, false, false);
  static SwitchOption interfaceDebugMEYes
    (interfaceDebugME,
     "Yes",
     "Print the debug information",
     true);
  static SwitchOption interfaceDebugMENo
    (interfaceDebugME,
     "No",
     "Do not print the debug information",
     false);

}

checkSettings() {


  if ((settings.flag("PartonLevel:ISR") || settings.flag("PartonLevel:FSR"))
    && settings.flag("MultipartonInteractions:allowDoubleRescatter")) {
    info.errorMsg("Warning in Pythia::checkSettings: "
        "double rescattering switched off since showering is on");
    settings.flag("MultipartonInteractions:allowDoubleRescatter", false);
  }

}

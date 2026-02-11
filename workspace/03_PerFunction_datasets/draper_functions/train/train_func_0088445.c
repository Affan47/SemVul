dofinish() {
  AnalysisHandler::dofinish();
  ofstream outZ ("pt_Z.dat");
  _Zpt.normaliseToCrossSection();
  _Zpt.simpleOutput(outZ,true);
  ofstream outWm ("pt_Wm.dat");
  _Wmpt.normaliseToCrossSection();
  _Wmpt.simpleOutput(outWm,true);
  ofstream outWp ("pt_Wp.dat");
  _Wppt.normaliseToCrossSection();
  _Wppt.simpleOutput(outWp,true);
}

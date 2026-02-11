doinit() {
  addToList(-1000024, 1000024, 23);
  addToList(-1000024, 1000037, 23);

  addToList(-1000037, 1000024, 23);
  addToList(-1000037, 1000037, 23);


  addToList(-1000024, 1000024, 22);
  addToList(-1000037, 1000037, 22);
  FFVVertex::doinit();
  tSusyBasePtr theSS = dynamic_ptr_cast<SusyBasePtr>(generator()->standardModel());
  if(!theSS)
    throw InitException() << "SSCCZVertex::doinit - The model pointer "
				     << "is null! "
				     << Exception::abortnow;
  _sw2 = sin2ThetaW();
  _cw = sqrt(1. - _sw2);
  _theU = theSS->charginoUMix();
  _theV = theSS->charginoVMix();
  if(!_theU || !_theV)
    throw InitException() << "SSCCZVertex::doinit - "
			  << "A mixing matrix pointer is null.  U: "
			  << _theU << "  V: " << _theV
			  << Exception::abortnow;
}

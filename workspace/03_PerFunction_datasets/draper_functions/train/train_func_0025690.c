logDSigHatDR(double effectiveJac) const {

  if ( !realEmissionME()->verbose() &&
       !underlyingBornME()->verbose() )
    return;

  tcStdXCombPtr bornxc = splitting() ? lastHeadXCombPtr() : lastXCombPtr();
  tcStdXCombPtr realxc = splitting() ? lastXCombPtr() : lastHeadXCombPtr();

  generator()->log() << "'" << name() << "' evaluated cross section using\n"
		     << "Born XComb " << bornxc << " real XComb " << realxc << "\n"
		     << "Jacobian = " << jacobian()
		     << " effective Jacobian = " << effectiveJac << "\n"
		     << "Born sHat/GeV2 = " << (bornxc->lastSHat()/GeV2)
		     << " real sHat/GeV2 = " << (realxc->lastSHat()/GeV2)
		     << " dsig/nb = "
		     << (lastMECrossSection()/nanobarn) << "\n" << flush;

}

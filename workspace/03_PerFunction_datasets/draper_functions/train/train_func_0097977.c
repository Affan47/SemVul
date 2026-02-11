logPDFWeight() const {

  if ( !theVerbose )
    return;

  generator()->log() << "'" << name() << "' calculated pdf weight = "
		     << lastMEPDFWeight() << " from XComb "
		     << lastXCombPtr() << "\n"
		     << "x1 = " << lastX1() << " (" << (mePartonData()[0]->coloured() ? "" : "not ") << "used) "
		     << "x2 = " << lastX2() << " (" << (mePartonData()[1]->coloured() ? "" : "not ") << "used)\n"
		     << flush;

}

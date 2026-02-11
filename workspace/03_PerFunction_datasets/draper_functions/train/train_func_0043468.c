dumpInfo(const string& prefix) const {
  generator()->log() << prefix << fullName()
		     << " [" << this << "]\n";
  generator()->log() << prefix << "  | XComb " << lastXCombPtr()
		     << " for ";
  if ( lastXCombPtr() ) {
    for ( cPDVector::const_iterator p = lastXComb().mePartonData().begin();
	  p != lastXComb().mePartonData().end(); ++p ) {
      generator()->log() << (**p).PDGName() << " ";
    }
  }
  generator()->log() << "\n";
}

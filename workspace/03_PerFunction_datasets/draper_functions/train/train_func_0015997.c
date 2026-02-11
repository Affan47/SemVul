splitDipoles(const cPDVector& born) {

  vector<Ptr<SubtractionDipole>::ptr> dips = dipoles();

  vector<Ptr<SubtractionDipole>::ptr> res;

  for ( vector<Ptr<SubtractionDipole>::ptr>::iterator d = dips.begin();
	d != dips.end(); ++d ) {
    for ( DiagramVector::const_iterator p = (**d).underlyingBornME()->diagrams().begin();
	  p != (**d).underlyingBornME()->diagrams().end(); ++p )
      if ( born == (**p).partons() ) {
	res.push_back(*d);
	break;
      }
  }

  return res;

}

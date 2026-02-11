getReferences() {
  IVector ret = MEGroup::getReferences();
  for ( vector<Ptr<SubtractionDipole>::ptr>::const_iterator d =
	  theDipoles.begin(); d != theDipoles.end(); ++d )
    ret.push_back(*d);
  return ret;
}

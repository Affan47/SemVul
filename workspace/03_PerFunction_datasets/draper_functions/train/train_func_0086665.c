rebind(const TranslationMap & trans) {
  for ( vector<Ptr<SubtractionDipole>::ptr>::iterator d =
	  theDipoles.begin(); d != theDipoles.end(); ++d )
    *d = trans.translate(*d);
  MEGroup::rebind(trans);
}

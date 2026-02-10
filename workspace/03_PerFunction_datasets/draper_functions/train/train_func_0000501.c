modeNumber(bool & cc, tcPDPtr parent,
				      const tPDVector & children) const {
  vector<long> id;
  id.push_back(parent->id());
  for(unsigned int ix=0;ix<children.size();++ix) id.push_back(children[ix]->id());
  return modeNumber(cc,id);
}

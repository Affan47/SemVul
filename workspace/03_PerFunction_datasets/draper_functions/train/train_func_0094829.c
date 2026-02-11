description () const {
  ostringstream desc;

  desc << "NestedDefs: successive application of " ;
  unsigned int i=1;
  for (list<JetDefinition>::const_iterator it=_defs.begin();it!=_defs.end();it++){
    desc << "Definition " << i++ << " [" << it->description() << "] - ";
  }

  return desc.str();
}

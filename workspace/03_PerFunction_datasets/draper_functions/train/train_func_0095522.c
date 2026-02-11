getReferences() {
  IVector ret = HwMEBase::getReferences();
  ret.push_back(_ggggvertex);
  ret.push_back(_gggvertex);
  ret.push_back(_qqgvertex);
  ret.push_back(_gluon);
  for(unsigned int ix=0;ix<_quark.size();++ix)
    {ret.push_back(_quark[ix]);}
  for(unsigned int ix=0;ix<_antiquark.size();++ix)
    {ret.push_back(_antiquark[ix]);}
  return ret;
}

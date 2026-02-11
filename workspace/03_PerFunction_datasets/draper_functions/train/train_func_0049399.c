fundamentalDomainInequalities()const
{
  set<ZVector> ret2;
  for(ElementContainer::const_iterator i=elements.begin();i!=elements.end();i++)
    ret2.insert(i->fundamentalDomainInequality());

  ZMatrix ret(0,sizeOfBaseSet());
  for(set<ZVector>::const_iterator i=ret2.begin();i!=ret2.end();i++)
    if(!i->isZero())ret.appendRow(*i);

  return ret;
}

getUniqueGenerators()const
{
  int n=sizeOfBaseSet();
  IntegerVectorList ret;

restart:
  SymmetryGroup temp(n);
  temp.computeClosure(ret);
  ElementContainer::const_iterator j=temp.elements.begin();
  for(ElementContainer::const_iterator i=elements.begin();i!=elements.end();i++,j++)
    {
      if(j==temp.elements.end() || *j!=*i)
        {
          ret.push_back(*i);
          goto restart;
        }
    }
  return ret;
}

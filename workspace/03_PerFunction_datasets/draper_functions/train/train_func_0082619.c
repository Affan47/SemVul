toStringJustCones(int dimLow, int dimHigh, bool onlyMaximal, bool group, std::ostream *multiplicities, bool compressed, bool tPlaneSort)const
{
  std::stringstream ret;

  ZVector additionalSortKeys(cones.size());


  for(int d=dimLow;d<=dimHigh;d++)
    {
      int numberOfOrbitsOutput=0;
      int numberOfOrbitsOfThisDimension=0;
      bool newDimension=true;

        {
          int I=0;
          for(ConeContainer::const_iterator i=cones.begin();i!=cones.end();i++,I++)

                  if(i->dimension==d)
                    {
                      numberOfOrbitsOfThisDimension++;
              if(!onlyMaximal || isMaximal(*i))
                {
                  numberOfOrbitsOutput++;
                  bool isMax=isMaximal(*i);
                  bool newOrbit=true;
                  std::set<std::set<int> > temp;
                    for(SymmetryGroup::ElementContainer::const_iterator k=sym.elements.begin();k!=sym.elements.end();k++)
                      {
                        Cone temp1=i->permuted(*k,*this,false);
                        temp.insert(temp1.indexSet());
                        if(compressed)break;
                    }
                  for(std::set<std::set<int> >::const_iterator j=temp.begin();j!=temp.end();j++)
                    {
                      ret << "{";
                      for(std::set<int>::const_iterator a=j->begin();a!=j->end();a++)
                        {
                          if(a!=j->begin())ret<<" ";
                          ret << *a;
                        }
                      ret << "}";
                      if(group)if(newOrbit)ret << "\t# New orbit";
                      if(newDimension)ret << "\t# Dimension "<<d;
                      ret <<std::endl;
                      if(isMax)if(multiplicities)
                        {
                          *multiplicities << i->multiplicity;
                          if(group)if(newOrbit)*multiplicities << "\t# New orbit";
                          if(newDimension)*multiplicities << "\t# Dimension "<<d;
                          *multiplicities << std::endl;
                        }
                      newOrbit=false;
                      newDimension=false;
                    }
              }
                    }
        }
    }

  return ret.str();
}

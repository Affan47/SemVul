conditional() const
{
  EStateIterVec itervec;
  if (enodeIter.size())
    {
      ENodeIter& subroot = (ENodeIter&) enodeIter[0];
      const TSpace tspace (subroot.terminals());
      itervec.push_back (&subroot.tstateIter[TransStart].A);
      itervec.push_back (&subroot.tstateIter[TransEnd].A);
      itervec.push_back (&subroot.tstateIter[TransWait].A);
      itervec.push_back (&subroot.tstateIter[TransStart].B);
      for (TTerm x = 0; x < subroot.terminals(); ++x)
	{
	  itervec.push_back (&subroot.ttermIter[x].Amd);
	  itervec.push_back (&subroot.tstateIter[tspace.TransInsertY(x)].B);
	  for (TTerm y = 0; y < subroot.terminals(); ++y)
	    itervec.push_back (&subroot.tstateIter[tspace.TransMatchXY(x,y)].B);
	}
    }
  return EStateUnionIterator (itervec);
}

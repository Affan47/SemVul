joint() const
{
  EStateIterVec itervec;
  if (enodeIter.size())
    {
      ENodeIter& subroot = (ENodeIter&) enodeIter[0];
      itervec.push_back (&subroot.tstateIter[TransStart].A);
      itervec.push_back (&subroot.tstateIter[TransEnd].A);
      itervec.push_back (&subroot.tstateIter[TransWait].A);
      itervec.push_back (&subroot.Bsi);
    }
  return EStateUnionIterator (itervec);
}

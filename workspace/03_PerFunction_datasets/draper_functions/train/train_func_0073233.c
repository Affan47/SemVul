IsRegInSet(SmallSet<unsigned, 32>& RegSet, unsigned Reg)
{

  for (MCRegAliasIterator AI(Reg, Subtarget->getRegisterInfo(), true);
       AI.isValid(); ++AI)
    if (RegSet.count(*AI))
      return true;
  return false;
}

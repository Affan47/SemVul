placeDebugValues() {

  if (FirstDbgValue) {
    BB->splice(RegionBegin, BB, FirstDbgValue);
    RegionBegin = FirstDbgValue;
  }

  for (std::vector<std::pair<MachineInstr *, MachineInstr *> >::iterator
         DI = DbgValues.end(), DE = DbgValues.begin(); DI != DE; --DI) {
    std::pair<MachineInstr *, MachineInstr *> P = *std::prev(DI);
    MachineInstr *DbgValue = P.first;
    MachineBasicBlock::iterator OrigPrevMI = P.second;
    if (&*RegionBegin == DbgValue)
      ++RegionBegin;
    BB->splice(++OrigPrevMI, BB, DbgValue);
    if (OrigPrevMI == std::prev(RegionEnd))
      RegionEnd = DbgValue;
  }
  DbgValues.clear();
  FirstDbgValue = nullptr;
}

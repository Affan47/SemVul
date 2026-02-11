getIRUnits(void)
{
  std::map<int, std::map<int, int> >::iterator it;
  int num, type, cycles,  x, y;
  ArArgumentBuilder *builder;

  for (it = myIRMap.begin(); it != myIRMap.end(); it++)
  {
    num = (*it).first;
    type = (*it).second[IR_TYPE];
    cycles = (*it).second[IR_CYCLES];
    x = (*it).second[IR_X];
    y = (*it).second[IR_Y];
    builder = new ArArgumentBuilder;
    builder->add("%d %d %d %d %d", num, type, cycles, x, y);
    myGetIRUnitList.push_back(builder);
  }
  return &myGetIRUnitList;
}

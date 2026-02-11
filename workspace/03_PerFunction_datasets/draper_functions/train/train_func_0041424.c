installNodeProperties()
{
  for (int i = 0; i < ComponentName::nIds; i++) {
    ComponentName::Id id = ComponentName::Id(i);
    nodePropertyTable_.insert(makeStringC(ComponentName::rcsName(id)), i);
    nodePropertyTable_.insert(makeStringC(ComponentName::sdqlName(id)), i);
  }
}

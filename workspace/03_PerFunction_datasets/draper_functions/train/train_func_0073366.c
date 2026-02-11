CountProgressMarksInAll(cmLocalUnixMakefileGenerator3* lg)
{
  size_t count = 0;
  std::set<cmTarget*> emitted;
  std::set<cmTarget*> const& targets = this->LocalGeneratorToTargetMap[lg];
  for(std::set<cmTarget*>::const_iterator t = targets.begin();
      t != targets.end(); ++t)
    {
    count += this->CountProgressMarksInTarget(*t, emitted);
    }
  return count;
}

GetTargetTotalNumberOfActions(cmTarget &target,
                                std::set<cmTarget *> &emitted)
{

  int result = 0;

  if(emitted.insert(&target).second)
    {
    cmLocalUnixMakefileGenerator3 *lg =
      static_cast<cmLocalUnixMakefileGenerator3 *>
      (target.GetMakefile()->GetLocalGenerator());
    result = static_cast<int>(lg->ProgressFiles[target.GetName()].size());

    TargetDependSet & depends = this->GetTargetDirectDepends(target);

    TargetDependSet::iterator i;
    for (i = depends.begin(); i != depends.end(); ++i)
      {
      result += this->GetTargetTotalNumberOfActions(**i, emitted);
      }
    }

  return result;
}

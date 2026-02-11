FillLocalGeneratorToTargetMap()
{
  this->LocalGeneratorToTargetMap.clear();

  for(std::vector<cmLocalGenerator*>::const_iterator
        lgi = this->LocalGenerators.begin();
      lgi != this->LocalGenerators.end(); ++lgi)
    {
    cmLocalGenerator* lg = *lgi;
    cmMakefile* mf = lg->GetMakefile();
    cmTargets& targets = mf->GetTargets();
    for(cmTargets::iterator t = targets.begin(); t != targets.end(); ++t)
      {
      cmTarget& target = t->second;


      for(cmLocalGenerator* clg = lg; clg && !this->IsExcluded(clg, target);
          clg = clg->GetParent())
        {

        std::set<cmTarget*>& targetSet =
          this->LocalGeneratorToTargetMap[clg];
        targetSet.insert(&target);


        TargetDependSet & tgtdeps = this->GetTargetDirectDepends(target);
        for(TargetDependSet::const_iterator ti = tgtdeps.begin();
            ti != tgtdeps.end(); ++ti)
          {
          targetSet.insert(*ti);
          }
        }
      }
    }
}

FindTargets(const char *propName,
                                                cmTarget *tgt,
                                                std::set<cmTarget*> &emitted)
{
  const char *prop = tgt->GetProperty(propName);
  if(!prop)
    {
    return std::string();
    }

  cmListFileBacktrace lfbt;
  cmGeneratorExpression ge(lfbt);

  cmGeneratorExpressionDAGChecker dagChecker(lfbt,
                                      tgt->GetName(),
                                      propName, 0, 0);

  cmsys::auto_ptr<cmCompiledGeneratorExpression> cge = ge.Parse(prop);

  cmTarget dummyHead;
  dummyHead.SetType(cmTarget::EXECUTABLE, "try_compile_dummy_exe");
  dummyHead.SetMakefile(tgt->GetMakefile());

  std::string result = cge->Evaluate(tgt->GetMakefile(), this->Config,
                                     false, &dummyHead, tgt, &dagChecker);

  const std::set<cmTarget*> &allTargets = cge->GetAllTargetsSeen();
  for(std::set<cmTarget*>::const_iterator li = allTargets.begin();
      li != allTargets.end(); ++li)
    {
    if(emitted.insert(*li).second)
      {
      this->Exports.push_back(*li);
      }
    }
  return result;
}

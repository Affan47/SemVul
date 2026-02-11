Generate()
{


  this->FilesReplacedDuringGenerate.clear();


  if(!this->CheckALLOW_DUPLICATE_CUSTOM_TARGETS())
    {
    return;
    }


  if(!this->CheckTargets())
    {
    return;
    }


  this->CreateAutomocTargets();


  unsigned int i;


  cmTargets globalTargets;
  this->CreateDefaultGlobalTargets(&globalTargets);
  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    cmMakefile* mf = this->LocalGenerators[i]->GetMakefile();
    cmTargets* targets = &(mf->GetTargets());
    cmTargets::iterator tit;
    for ( tit = globalTargets.begin(); tit != globalTargets.end(); ++ tit )
      {
      (*targets)[tit->first] = tit->second;
      (*targets)[tit->first].SetMakefile(mf);
      }
    }


  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    this->LocalGenerators[i]->AddHelperCommands();
    }


  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    this->LocalGenerators[i]->TraceDependencies();
    }


  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    this->LocalGenerators[i]->GenerateTargetManifest();
    }


  if(!this->ComputeTargetDepends())
    {
    return;
    }


  this->FillLocalGeneratorToTargetMap();


  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    this->SetCurrentLocalGenerator(this->LocalGenerators[i]);
    this->LocalGenerators[i]->Generate();
    this->LocalGenerators[i]->GenerateInstallRules();
    this->LocalGenerators[i]->GenerateTestFiles();
    this->CMakeInstance->UpdateProgress("Generating",
      (static_cast<float>(i)+1.0f)/
       static_cast<float>(this->LocalGenerators.size()));
    }
  this->SetCurrentLocalGenerator(0);


  this->CheckRuleHashes();

  this->WriteSummary();

  if (this->ExtraGenerator != 0)
    {
    this->ExtraGenerator->Generate();
    }

  this->CMakeInstance->UpdateProgress("Generating done", -1);
}

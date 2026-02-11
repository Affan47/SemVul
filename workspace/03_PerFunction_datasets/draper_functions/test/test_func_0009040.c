FindTargetToLink(int depender_index,
                                                 const char* name)
{

  cmMakefile* mf = this->Makefile;
  if(depender_index >= 0)
    {
    if(cmTarget* depender = this->EntryList[depender_index].Target)
      {
      mf = depender->GetMakefile();
      }
    }
  cmTarget* tgt = mf->FindTargetToUse(name);


  if(tgt && tgt->GetType() == cmTarget::EXECUTABLE &&
     !tgt->IsExecutableWithExports())
    {
    tgt = 0;
    }


  return tgt;
}

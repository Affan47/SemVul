cmakemainGetMakefile(void *clientdata)
{
  cmake* cm = (cmake *)clientdata;
  if(cm && cm->GetDebugOutput())
    {
    cmGlobalGenerator* gg=cm->GetGlobalGenerator();
    if (gg)
      {
      cmLocalGenerator* lg=gg->GetCurrentLocalGenerator();
      if (lg)
        {
        cmMakefile* mf = lg->GetMakefile();
        return mf;
        }
      }
    }
  return 0;
}

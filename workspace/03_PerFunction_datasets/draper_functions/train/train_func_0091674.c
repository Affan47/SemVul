CreateLocalGenerator()
{
  cmLocalGenerator* lg = new cmLocalNinjaGenerator;
  lg->SetGlobalGenerator(this);
  return lg;
}

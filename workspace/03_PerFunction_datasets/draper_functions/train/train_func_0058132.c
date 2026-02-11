Verify(const DataSet& ds) const
{
  MediaStorage ms;
  ms.SetFromDataSet(ds);

  const IODs &iods = GetIODs();
  const Modules &modules = GetModules();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented" );
    return false;
    }
  const IOD &iod = iods.GetIOD( iodname );


  size_t niods = iod.GetNumberOfIODs();
  bool v = true;

  for(size_t idx = 0; idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();
    Usage::UsageType ut = iodentry.GetUsageType();

    const Module &module = modules.GetModule( ref );

    v = v && module.Verify( ds, ut );
    }

  return v;

}

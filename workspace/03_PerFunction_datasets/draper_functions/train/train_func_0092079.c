GetTypeFromTag(const File& file, const Tag& tag) const
{
  Type ret;
  MediaStorage ms;
  ms.SetFromFile(file);

  const IODs &iods = GetIODs();
  const Modules &modules = GetModules();
  const char *iodname = GetIODNameFromMediaStorage( ms );
  if( !iodname )
    {
    gdcmErrorMacro( "Not implemented: " << ms );
    return ret;
    }
  const IOD &iod = iods.GetIOD( iodname );
  const Macros &macros = GetMacros();

  IOD::SizeType niods = iod.GetNumberOfIODs();

  for(unsigned int idx = 0; idx < niods; ++idx)
    {
    const IODEntry &iodentry = iod.GetIODEntry(idx);
    const char *ref = iodentry.GetRef();


    const Module &module = modules.GetModule( ref );
    if( module.FindModuleEntryInMacros(macros, tag ) )
      {
      const ModuleEntry &module_entry = module.GetModuleEntryInMacros(macros,tag);
      ret = module_entry.GetType();
      }
    }

  return ret;
}

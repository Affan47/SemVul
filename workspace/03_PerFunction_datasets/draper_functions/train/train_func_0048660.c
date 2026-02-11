StartXML(std::ostream& ostr, bool append)
{
  if(this->CurrentTag.empty())
    {
    cmCTestLog(this, ERROR_MESSAGE,
               "Current Tag empty, this may mean"
               " NightlStartTime was not set correctly." << std::endl);
    cmSystemTools::SetFatalErrorOccured();
    }

  cmsys::SystemInformation info;
  info.RunCPUCheck();
  info.RunOSCheck();
  info.RunMemoryCheck();
  ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName")
       << "\"\n\tBuildStamp=\"" << this->CurrentTag << "-"
       << this->GetTestModelString() << "\"\n\tName=\""
       << this->GetCTestConfiguration("Site") << "\"\n\tGenerator=\"ctest-"
       << cmVersion::GetCMakeVersion()  << "\"\n"
       << (append? "\tAppend=\"true\"\n":"")
       << "\tCompilerName=\"" << this->GetCTestConfiguration("Compiler")
       << "\"\n"
#ifdef _COMPILER_VERSION
       << "\tCompilerVersion=\"_COMPILER_VERSION\"\n"
#endif
       << "\tOSName=\"" << info.GetOSName() << "\"\n"
       << "\tHostname=\"" << info.GetHostname() << "\"\n"
       << "\tOSRelease=\"" << info.GetOSRelease() << "\"\n"
       << "\tOSVersion=\"" << info.GetOSVersion() << "\"\n"
       << "\tOSPlatform=\"" << info.GetOSPlatform() << "\"\n"
       << "\tIs64Bits=\"" << info.Is64Bits() << "\"\n"
       << "\tVendorString=\"" << info.GetVendorString() << "\"\n"
       << "\tVendorID=\"" << info.GetVendorID() << "\"\n"
       << "\tFamilyID=\"" << info.GetFamilyID() << "\"\n"
       << "\tModelID=\"" << info.GetModelID() << "\"\n"
       << "\tProcessorCacheSize=\"" << info.GetProcessorCacheSize() << "\"\n"
       << "\tNumberOfLogicalCPU=\"" << info.GetNumberOfLogicalCPU() << "\"\n"
       << "\tNumberOfPhysicalCPU=\""<< info.GetNumberOfPhysicalCPU() << "\"\n"
       << "\tTotalVirtualMemory=\"" << info.GetTotalVirtualMemory() << "\"\n"
       << "\tTotalPhysicalMemory=\""<< info.GetTotalPhysicalMemory() << "\"\n"
       << "\tLogicalProcessorsPerPhysical=\""
       << info.GetLogicalProcessorsPerPhysical() << "\"\n"
       << "\tProcessorClockFrequency=\""
       << info.GetProcessorClockFrequency() << "\"\n"
       << ">" << std::endl;
  this->AddSiteProperties(ostr);
}

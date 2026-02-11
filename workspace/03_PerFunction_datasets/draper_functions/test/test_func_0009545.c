testSystemInformation(int, char*[])
{
  kwsys::SystemInformation info;
  info.RunCPUCheck();
  info.RunOSCheck();
  info.RunMemoryCheck();
  printMethod(info, GetOSName);
  printMethod(info, GetHostname);
  printMethod(info, GetOSRelease);
  printMethod(info, GetOSVersion);
  printMethod(info, GetOSPlatform);
  printMethod(info, GetVendorString);
  printMethod(info, GetVendorID);
  printMethod(info, GetTypeID);
  printMethod(info, GetFamilyID);
  printMethod(info, GetModelID);
  printMethod(info, GetExtendedProcessorName);
  printMethod(info, GetProcessorSerialNumber);
  printMethod2(info, GetProcessorCacheSize, "KB");
  printMethod(info, GetLogicalProcessorsPerPhysical);
  printMethod2(info, GetProcessorClockFrequency, "MHz");
  printMethod(info, Is64Bits);
  printMethod(info, GetNumberOfLogicalCPU);
  printMethod(info, GetNumberOfPhysicalCPU);
  printMethod(info, DoesCPUSupportCPUID);
  printMethod(info, GetProcessorAPICID);
  printMethod2(info, GetTotalVirtualMemory, "MB");
  printMethod2(info, GetAvailableVirtualMemory, "MB");
  printMethod2(info, GetTotalPhysicalMemory, "MB");
  printMethod2(info, GetAvailablePhysicalMemory, "MB");


  return 0;
}

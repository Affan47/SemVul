QuerySolarisProcessor()
{
  if (!this->QueryProcessorBySysconf())
    {
    return false;
    }


  this->CPUSpeedInMHz = static_cast<float>(atoi(this->ParseValueFromKStat("-s clock_MHz").c_str()));


  this->ChipID.Family = 0;


  this->ChipID.ProcessorName = this->ParseValueFromKStat("-s cpu_type");
  this->ChipID.Model = 0;


  if (this->ChipID.ProcessorName != "i386")
    {
    this->ChipID.Vendor = "Sun";
    this->FindManufacturer();
    }

  return true;
}

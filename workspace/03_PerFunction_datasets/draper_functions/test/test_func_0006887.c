GetOSDescription()
{
  kwsys_ios::ostringstream oss;
  oss
    << this->GetOSName()
    << " "
    << this->GetOSRelease()
    << " "
    << this->GetOSVersion();

  return oss.str();
}

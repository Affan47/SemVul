Initialize(UserInformation const & inUserInformation,
        const char *inCalledAETitle, const char *inCallingAETitle,
        unsigned long inCalledIPAddress, int inCalledIPPort,
        std::string inCalledComputerName)
{
  if (inCalledIPAddress == 0 && inCalledComputerName.empty()){
    return false;
  }
  assert( inCalledAETitle );
  assert( inCallingAETitle );
  assert( AAssociateRQPDU::IsAETitleValid( inCalledAETitle ) );
  assert( AAssociateRQPDU::IsAETitleValid( inCallingAETitle ) );
  const size_t lcalled  = strlen( inCalledAETitle );
  const size_t lcalling = strlen( inCallingAETitle );
  mCalledAETitle = std::string(inCalledAETitle, lcalled > 16 ? 16 : lcalled );
  mCallingAETitle = std::string(inCallingAETitle, lcalling > 16 ? 16 : lcalling );
  mCalledComputerName = inCalledComputerName;
  mCalledIPPort = inCalledIPPort;
  mCalledIPAddress = inCalledIPAddress;


  if (mCalledIPAddress == 0 && !mCalledComputerName.empty()){
    mCalledIPAddress = inet_addr(mCalledComputerName.c_str());


  }


  (void)inUserInformation;
  return true;
}

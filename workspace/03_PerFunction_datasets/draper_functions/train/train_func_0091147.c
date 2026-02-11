DownloadBitstream(const char* uuid,const char* filename)
{
  std::stringstream query;
  query << "SELECT b.internal_id,b.name,bh.handle,bh.priority FROM bitstream AS b ";
  query << "LEFT OUTER JOIN bitstream2handle AS bh ON b.bitstream_id=bh.bitstream_id WHERE b.uuid='";
  query << uuid;
  query << "' ORDER BY bh.priority DESC";

  if(!m_Database->ExecuteQuery(query.str().c_str()))
    {
    std::cerr << m_Database->GetErrorMessage() << std::endl;
    return "";
    }

  bool firstrow = true;
  std::string internalHandle = "";

  while(m_Database->GetNextRow())
    {
    if(firstrow)
      {
      std::string internalId = m_Database->GetValueAsString(0);
      internalHandle = "assetstore/";
      internalHandle += internalId.substr(0,2);
      internalHandle += "/";
      internalHandle += internalId.substr(2,2);
      internalHandle += "/";
      internalHandle += internalId.substr(4,2);
      internalHandle += "/";
      internalHandle += internalId;
      firstrow = false;
      }


    int priority = m_Database->GetValueAsInt(3);
    if(priority == 0)
      {
      return internalHandle;
      }
    else
      {

      std::string handle = m_Database->GetValueAsString(2);
      if(kwsys::SystemTools::FileExists(handle.c_str(),true))
        {
        return handle;
        }
      }
    }


  return internalHandle;
}

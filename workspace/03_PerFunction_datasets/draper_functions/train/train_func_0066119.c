operator>>(std::istream & stream, VMMapData_10_2 & data)
{
  MapRecord *record = ITK_NULLPTR;


  data.Reset();
  try
    {
    std::string    line;


    while ( std::getline(stream, line).good() )
      {
      if ( line.find("==== Summary for process", 0) != std::string::npos )
        {
        break;
        }
      }

    while ( std::getline(stream, line).good() )
      {
      if ( line.find("REGION TYPE", 0) != std::string::npos )
        {
        break;
        }
      }

    if ( !std::getline(stream, line).good() )
      {


      stream.clear();
      stream.seekg(0, std::ios_base::beg);

      while ( std::getline(stream, line).good() )
        {
        if ( line.find("==== Writable regions for process", 0) != std::string::npos )
          {
          break;
          }
        }
      if ( stream.fail() )
        {
        itkGenericExceptionMacro(<< "Can't find the \"Writable regions\" section, can't read the memory records.");
        }
      data.m_UsingSummary = false;
      }
    else
      {
      data.m_UsingSummary = true;
      }
    if ( data.m_UsingSummary )
      {
      record = new VMMapSummaryRecord;

      while ( stream >> *static_cast< VMMapSummaryRecord * >( record ) )
        {
        if ( record->m_RecordName.empty() )
          {
          break;
          }
        data.m_Records.push_back(record);
        record = new VMMapSummaryRecord;
        }
      }
    else
      {
      record = new VMMapRecord;

      while ( stream >> *dynamic_cast< VMMapRecord * >( record ) )
        {
        if ( record->m_RecordName.empty() )
          {
          break;
          }
        data.m_Records.push_back(record);
        record = new VMMapRecord;
        }
      }
    }
  catch ( ExceptionObject & excp )
    {

    data.Reset();

    itkGenericExceptionMacro(<< "The VMMap stream contains errors, can't read the memory records." << excp);
    }

  delete record;
  return stream;
}

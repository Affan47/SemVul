WriteLogOutputTop(size_t completed, size_t total)
{
  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(getNumWidth(total))
             << completed << "/");
  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(getNumWidth(total))
             << total << " ");

  if ( this->TestHandler->MemCheck )
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "MemCheck");
    }
  else
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Test");
    }

  cmOStringStream indexStr;
  indexStr << " #" << this->Index << ":";
  cmCTestLog(this->CTest, HANDLER_OUTPUT,
             std::setw(3 + getNumWidth(this->TestHandler->GetMaxIndex()))
             << indexStr.str().c_str());
  cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
  const int maxTestNameWidth = this->CTest->GetMaxTestNameWidth();
  std::string outname = this->TestProperties->Name + " ";
  outname.resize(maxTestNameWidth + 4, '.');

  *this->TestHandler->LogFile << this->TestProperties->Index << "/"
    << this->TestHandler->TotalNumberOfTests << " Testing: "
    << this->TestProperties->Name << std::endl;
  *this->TestHandler->LogFile << this->TestProperties->Index << "/"
    << this->TestHandler->TotalNumberOfTests
    << " Test: " << this->TestProperties->Name.c_str() << std::endl;
  *this->TestHandler->LogFile << "Command: \"" << this->ActualCommand << "\"";

  for (std::vector<std::string>::iterator i = this->Arguments.begin();
       i != this->Arguments.end(); ++i)
    {
    *this->TestHandler->LogFile
      << " \"" << i->c_str() << "\"";
    }
  *this->TestHandler->LogFile << std::endl
    << "Directory: " << this->TestProperties->Directory << std::endl
    << "\"" << this->TestProperties->Name.c_str() << "\" start time: "
    << this->StartTime << std::endl;

  *this->TestHandler->LogFile
    << "Output:" << std::endl
    << "----------------------------------------------------------"
    << std::endl;
  *this->TestHandler->LogFile
    << this->ProcessOutput.c_str() << "<end of output>" << std::endl;

  cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
  cmCTestLog(this->CTest, DEBUG, "Testing "
             << this->TestProperties->Name.c_str() << " ... ");
}

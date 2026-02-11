PostProcessBoundsCheckerTest(cmCTestTestResult& res)
{
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
             "PostProcessBoundsCheckerTest for : "
             << res.Name.c_str() << std::endl);
  if ( !cmSystemTools::FileExists(this->MemoryTesterOutputFile.c_str()) )
    {
    std::string log = "Cannot find memory tester output file: "
      + this->MemoryTesterOutputFile;
    cmCTestLog(this->CTest, ERROR_MESSAGE, log.c_str() << std::endl);
    return;
    }

  {
  std::ifstream ifs(this->MemoryTesterOutputFile.c_str());
  if ( !ifs )
    {
    std::string log = "Cannot read memory tester output file: "
      + this->MemoryTesterOutputFile;
    cmCTestLog(this->CTest, ERROR_MESSAGE, log.c_str() << std::endl);
    return;
    }
  res.Output += BOUNDS_CHECKER_MARKER;
  res.Output += "\n";
  std::string line;
  while ( cmSystemTools::GetLineFromStream(ifs, line) )
    {
    res.Output += line;
    res.Output += "\n";
    }
  }
  cmSystemTools::Delay(1000);
  cmSystemTools::RemoveFile(this->BoundsCheckerDPBDFile.c_str());
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Remove: "
    << this->BoundsCheckerDPBDFile.c_str() << std::endl);
  cmSystemTools::RemoveFile(this->BoundsCheckerXMLFile.c_str());
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Remove: "
    << this->BoundsCheckerXMLFile.c_str() << std::endl);
}

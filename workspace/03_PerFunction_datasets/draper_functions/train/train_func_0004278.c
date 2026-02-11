StartTest(size_t total)
{
  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(2*getNumWidth(total) + 8)
    << "Start "
    << std::setw(getNumWidth(this->TestHandler->GetMaxIndex()))
    << this->TestProperties->Index << ": "
    << this->TestProperties->Name << std::endl);
  this->ComputeArguments();
  std::vector<std::string>& args = this->TestProperties->Args;
  this->TestResult.Properties = this->TestProperties;
  this->TestResult.ExecutionTime = 0;
  this->TestResult.CompressOutput = false;
  this->TestResult.ReturnValue = -1;
  this->TestResult.CompletionStatus = "Failed to start";
  this->TestResult.Status = cmCTestTestHandler::BAD_COMMAND;
  this->TestResult.TestCount = this->TestProperties->Index;
  this->TestResult.Name = this->TestProperties->Name;
  this->TestResult.Path = this->TestProperties->Directory.c_str();


  for(std::vector<std::string>::iterator i =
    this->TestProperties->RequiredFiles.begin();
    i != this->TestProperties->RequiredFiles.end(); ++i)
    {
    std::string file = *i;

    if(!cmSystemTools::FileExists(file.c_str()))
      {

      this->TestProcess = new cmProcess;
      *this->TestHandler->LogFile << "Unable to find required file: "
               << file.c_str() << std::endl;
      cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find required file: "
               << file.c_str() << std::endl);
      this->TestResult.Output = "Unable to find required file: " + file;
      this->TestResult.FullCommandLine = "";
      this->TestResult.CompletionStatus = "Not Run";
      this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
      return false;
      }
    }

  if (this->ActualCommand == "")
    {


    this->TestProcess = new cmProcess;
    *this->TestHandler->LogFile << "Unable to find executable: "
                   << args[1].c_str() << std::endl;
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
               << args[1].c_str() << std::endl);
    this->TestResult.Output = "Unable to find executable: " + args[1];
    this->TestResult.FullCommandLine = "";
    this->TestResult.CompletionStatus = "Not Run";
    this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
    return false;
    }
  this->StartTime = this->CTest->CurrentTime();

  return this->ForkProcess(this->ResolveTimeout(),
                             &this->TestProperties->Environment);
}

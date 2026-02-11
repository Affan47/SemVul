CreateCMake()
{

  if (this->CMake)
    {
    delete this->CMake;
    delete this->GlobalGenerator;
    delete this->LocalGenerator;
    }
  this->CMake = new cmake;
  this->CMake->AddCMakePaths();
  this->GlobalGenerator = new cmGlobalGenerator;
  this->GlobalGenerator->SetCMakeInstance(this->CMake);

  this->LocalGenerator = this->GlobalGenerator->CreateLocalGenerator();
  this->LocalGenerator->SetGlobalGenerator(this->GlobalGenerator);
  this->Makefile = this->LocalGenerator->GetMakefile();


  this->CMake->RemoveUnscriptableCommands();


  this->AddCTestCommand(new cmCTestBuildCommand);
  this->AddCTestCommand(new cmCTestConfigureCommand);
  this->AddCTestCommand(new cmCTestCoverageCommand);
  this->AddCTestCommand(new cmCTestEmptyBinaryDirectoryCommand);
  this->AddCTestCommand(new cmCTestMemCheckCommand);
  this->AddCTestCommand(new cmCTestReadCustomFilesCommand);
  this->AddCTestCommand(new cmCTestRunScriptCommand);
  this->AddCTestCommand(new cmCTestSleepCommand);
  this->AddCTestCommand(new cmCTestStartCommand);
  this->AddCTestCommand(new cmCTestSubmitCommand);
  this->AddCTestCommand(new cmCTestTestCommand);
  this->AddCTestCommand(new cmCTestUpdateCommand);
}

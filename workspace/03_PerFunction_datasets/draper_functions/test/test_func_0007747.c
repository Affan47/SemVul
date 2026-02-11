WriteSpecialTargetsBottom(std::ostream& makefileStream)
{
  this->WriteDivider(makefileStream);
  makefileStream
    << "# Special targets to cleanup operation of make.\n"
    << "\n";


  {

  std::string cmakefileName = cmake::GetCMakeFilesDirectoryPostSlash();
  cmakefileName += "Makefile.cmake";
  std::string runRule =
    "$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)";
  runRule += " --check-build-system ";
  runRule += this->Convert(cmakefileName.c_str(),NONE,SHELL);
  runRule += " 0";

  std::vector<std::string> no_depends;
  std::vector<std::string> commands;
  commands.push_back(runRule);
  if(this->Parent)
    {
    this->CreateCDCommand(commands,
                          this->Makefile->GetHomeOutputDirectory(),
                          cmLocalGenerator::START_OUTPUT);
    }
  this->WriteMakeRule(makefileStream,
                      "Special rule to run CMake to check the build system "
                      "integrity.\n"
                      "No rule that depends on this can have "
                      "commands that come from listfiles\n"
                      "because they might be regenerated.",
                      "cmake_check_build_system",
                      no_depends,
                      commands, true);
  }
}

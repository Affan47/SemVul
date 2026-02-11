compileProgram(const std::string &Bitcode,
                                    std::string *Error,
                                    unsigned Timeout,
                                    unsigned MemoryLimit) {

  std::vector<const char*> ProgramArgs;
  ProgramArgs.push_back(CompilerCommand.c_str());

  for (std::size_t i = 0; i < CompilerArgs.size(); ++i)
    ProgramArgs.push_back(CompilerArgs.at(i).c_str());
  ProgramArgs.push_back(Bitcode.c_str());
  ProgramArgs.push_back(nullptr);


  for (unsigned i = 0, e = CompilerArgs.size(); i != e; ++i)
    ProgramArgs.push_back(CompilerArgs[i].c_str());

  if (RunProgramWithTimeout(CompilerCommand, &ProgramArgs[0],
                             "", "", "",
                             Timeout, MemoryLimit, Error))
    *Error = ProcessFailure(CompilerCommand, &ProgramArgs[0],
                           Timeout, MemoryLimit);
}

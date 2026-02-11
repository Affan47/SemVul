TestMergedProgram(const BugDriver &BD, Module *M1, Module *M2,
                                 bool DeleteInputs, std::string &Error,
                                 bool &Broken) {

  if (!DeleteInputs) {
    M1 = CloneModule(M1);
    M2 = CloneModule(M2);
  }
  if (Linker::LinkModules(M1, M2))
    exit(1);
  delete M2;


  Broken = BD.diffProgram(M1, "", "", false, &Error);
  if (!Error.empty()) {

    delete M1;
    return nullptr;
  }
  return M1;
}

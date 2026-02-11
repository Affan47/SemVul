FindSymbol(const string& name) {
  Symbol result = FindSymbolNotEnforcingDeps(name);

  if (!pool_->enforce_dependencies_) {

    return result;
  }


  const FileDescriptor* file = result.GetFile();
  if (file == file_) return result;
  for (int i = 0; i < file_->dependency_count(); i++) {
    if (file == file_->dependency(i)) return result;
  }

  if (result.type == Symbol::PACKAGE) {


    if (IsInPackage(file_, name)) return result;
    for (int i = 0; i < file_->dependency_count(); i++) {

      if (file_->dependency(i) != NULL &&
          IsInPackage(file_->dependency(i), name)) {
        return result;
      }
    }
  }

  possible_undeclared_dependency_ = file;
  possible_undeclared_dependency_name_ = name;
  return kNullSymbol;
}

getPointerToNamedFunction(const std::string &Name,
                                                     bool AbortOnFailure) {
  uint64_t Addr = getSymbolAddress(Name);

  if (!Addr && AbortOnFailure)
    report_fatal_error("Program used external function '" + Name +
                       "' which could not be resolved!");
  return (void*)Addr;
}

getName(StringRef &Result) const {
  uintptr_t IntPtr = 0;
  if (std::error_code EC = OwningObject->getRvaPtr(Table[Index].Name, IntPtr))
    return EC;
  Result = StringRef(reinterpret_cast<const char *>(IntPtr));
  return std::error_code();
}

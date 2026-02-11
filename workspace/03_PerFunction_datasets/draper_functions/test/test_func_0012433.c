Initialize(void* address)
{
  this->Address = address;
#if defined(KWSYS_SYSTEMINFORMATION_HAS_SYMBOL_LOOKUP)

  Dl_info info;
  int ierr = dladdr(this->Address, &info);
  if (ierr && info.dli_sname && info.dli_saddr) {
    this->SetBinary(info.dli_fname);
    this->SetFunction(info.dli_sname);
  }
#else


#endif
}

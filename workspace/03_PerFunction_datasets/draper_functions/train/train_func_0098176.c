DoDeAllocHidden(void** ptr) {
  Use(ptr);
  void* p = *ptr;
  VLOG(2) << "Deallocating hidden " << p;
  UnHide(&p);
  delete [] reinterpret_cast<char*>(p);
}

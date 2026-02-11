uv_dlsym(uv_lib_t library, const char* name, void** ptr) {
  void* address;


  dlerror();

  address = dlsym(library, name);

  if (dlerror()) {
    return uv_inval_;
  }

  *ptr = (void*) address;
  return uv_ok_;
}

uv_dlopen(const char* filename, uv_lib_t* library) {
  void* handle = dlopen(filename, RTLD_LAZY);
  if (handle == NULL) {
    return uv_inval_;
  }

  *library = handle;
  return uv_ok_;
}

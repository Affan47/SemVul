uv_dlclose(uv_lib_t library) {
  if (dlclose(library) != 0) {
    return uv_inval_;
  }

  return uv_ok_;
}

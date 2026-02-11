Cwd(const Arguments& args) {
  HandleScope scope;
#ifdef _WIN32

  char buf[MAX_PATH * 4 + 1];
#else
  char buf[PATH_MAX + 1];
#endif

  uv_err_t r = uv_cwd(buf, ARRAY_SIZE(buf) - 1);
  if (r.code != UV_OK) {
    return ThrowException(UVException(r.code, "uv_cwd"));
  }

  buf[ARRAY_SIZE(buf) - 1] = '\0';
  Local<String> cwd = String::New(buf);

  return scope.Close(cwd);
}

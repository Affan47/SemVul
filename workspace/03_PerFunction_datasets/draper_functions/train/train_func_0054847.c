MKDir(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsInt32()) {
    return THROW_BAD_ARGS;
  }

  String::Utf8Value path(args[0]->ToString());
  mode_t mode = static_cast<mode_t>(args[1]->Int32Value());

  if (args[2]->IsFunction()) {
    ASYNC_CALL(mkdir, args[2], *path, mode)
  } else {
#ifdef __MINGW32__
    int ret = mkdir(*path);
#else
    int ret = mkdir(*path, mode);
#endif
    if (ret != 0) return ThrowException(ErrnoException(errno, NULL, "", *path));
    return Undefined();
  }
}

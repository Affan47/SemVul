FStat(const Arguments& args) {
  HandleScope scope;

  if (args.Length() < 1 || !args[0]->IsInt32()) {
    return THROW_BAD_ARGS;
  }

  int fd = args[0]->Int32Value();

  if (args[1]->IsFunction()) {
    ASYNC_CALL(fstat, args[1], fd)
  } else {
    NODE_STAT_STRUCT s;
    int ret = NODE_FSTAT(fd, &s);
    if (ret != 0) return ThrowException(ErrnoException(errno));
    return scope.Close(BuildStatsObject(&s));
  }
}

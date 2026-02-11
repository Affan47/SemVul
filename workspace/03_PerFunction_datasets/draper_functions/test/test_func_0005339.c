ComputeCallInitialize(int argc,
                                              InLoopFlag in_loop,
                                              Code::Kind kind) {
  Code::Flags flags = Code::ComputeFlags(kind,
                                         in_loop,
                                         UNINITIALIZED,
                                         Code::kNoExtraICState,
                                         NORMAL,
                                         argc);
  Object* probe;
  { MaybeObject* maybe_probe = ProbeCache(flags);
    if (!maybe_probe->ToObject(&probe)) return maybe_probe;
  }
  if (!probe->IsUndefined()) return probe;
  StubCompiler compiler;
  return FillCache(compiler.CompileCallInitialize(flags));
}

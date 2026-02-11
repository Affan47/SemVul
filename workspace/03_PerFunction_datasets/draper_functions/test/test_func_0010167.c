GetCode(PropertyType type,
                                            String* name,
                                            InlineCacheState state) {
  Code::Flags flags = Code::ComputeFlags(
      Code::KEYED_LOAD_IC, state, Code::kNoExtraICState, type);
  MaybeObject* result = GetCodeWithFlags(flags, name);
  if (!result->IsFailure()) {
    PROFILE(isolate(),
            CodeCreateEvent(Logger::KEYED_LOAD_IC_TAG,
                            Code::cast(result->ToObjectUnchecked()),
                            name));
    GDBJIT(AddCode(GDBJITInterface::LOAD_IC,
                   name,
                   Code::cast(result->ToObjectUnchecked())));
  }
  return result;
}

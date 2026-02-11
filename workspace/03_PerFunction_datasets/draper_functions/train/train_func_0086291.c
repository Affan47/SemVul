CompileCallDebugBreak(Code::Flags flags) {
  HandleScope scope;
  Debug::GenerateCallICDebugBreak(masm());
  Object* result;
  { MaybeObject* maybe_result =
        GetCodeWithFlags(flags, "CompileCallDebugBreak");
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }
  Code* code = Code::cast(result);
  USE(code);
  Code::Kind kind = Code::ExtractKindFromFlags(flags);
  USE(kind);
  PROFILE(CodeCreateEvent(CALL_LOGGER_TAG(kind, CALL_DEBUG_BREAK_TAG),
                          code, code->arguments_count()));
  return result;
}

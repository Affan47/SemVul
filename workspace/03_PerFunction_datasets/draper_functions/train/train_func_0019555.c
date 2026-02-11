ComputeKeyedStoreSpecialized(
    JSObject* receiver,
    StrictModeFlag strict_mode) {
  Code::Flags flags =
      Code::ComputeMonomorphicFlags(Code::KEYED_STORE_IC, NORMAL, strict_mode);
  String* name = Heap::KeyedStoreSpecialized_symbol();
  Object* code = receiver->map()->FindInCodeCache(name, flags);
  if (code->IsUndefined()) {
    KeyedStoreStubCompiler compiler(strict_mode);
    { MaybeObject* maybe_code = compiler.CompileStoreSpecialized(receiver);
      if (!maybe_code->ToObject(&code)) return maybe_code;
    }
    PROFILE(CodeCreateEvent(Logger::KEYED_STORE_IC_TAG, Code::cast(code), 0));
    Object* result;
    { MaybeObject* maybe_result =
          receiver->UpdateMapCodeCache(name, Code::cast(code));
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }
  }
  return code;
}

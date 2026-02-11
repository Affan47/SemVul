ComputeStoreCallback(
    String* name,
    JSObject* receiver,
    AccessorInfo* callback,
    StrictModeFlag strict_mode) {
  ASSERT(v8::ToCData<Address>(callback->setter()) != 0);
  Code::Flags flags = Code::ComputeMonomorphicFlags(
      Code::STORE_IC, CALLBACKS, strict_mode);
  Object* code = receiver->map()->FindInCodeCache(name, flags);
  if (code->IsUndefined()) {
    StoreStubCompiler compiler(strict_mode);
    { MaybeObject* maybe_code =
          compiler.CompileStoreCallback(receiver, callback, name);
      if (!maybe_code->ToObject(&code)) return maybe_code;
    }
    PROFILE(isolate_,
            CodeCreateEvent(Logger::STORE_IC_TAG, Code::cast(code), name));
    GDBJIT(AddCode(GDBJITInterface::STORE_IC, name, Code::cast(code)));
    Object* result;
    { MaybeObject* maybe_result =
          receiver->UpdateMapCodeCache(name, Code::cast(code));
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }
  }
  return code;
}

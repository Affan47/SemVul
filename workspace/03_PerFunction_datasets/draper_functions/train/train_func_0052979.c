ComputeKeyedLoadPixelArray(JSObject* receiver) {


  Code::Flags flags =
      Code::ComputeMonomorphicFlags(Code::KEYED_LOAD_IC, NORMAL);
  String* name = Heap::KeyedLoadPixelArray_symbol();
  Object* code = receiver->map()->FindInCodeCache(name, flags);
  if (code->IsUndefined()) {
    KeyedLoadStubCompiler compiler;
    { MaybeObject* maybe_code = compiler.CompileLoadPixelArray(receiver);
      if (!maybe_code->ToObject(&code)) return maybe_code;
    }
    PROFILE(CodeCreateEvent(Logger::KEYED_LOAD_IC_TAG, Code::cast(code), 0));
    Object* result;
    { MaybeObject* maybe_result =
          receiver->UpdateMapCodeCache(name, Code::cast(code));
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }
  }
  return code;
}

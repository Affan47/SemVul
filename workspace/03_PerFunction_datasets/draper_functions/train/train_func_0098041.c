ScriptGetEvalFromScriptPosition(Object* object, void*) {
  HandleScope scope;
  Handle<Script> script(Script::cast(JSValue::cast(object)->value()));


  int compilation_type = Smi::cast(script->compilation_type())->value();
  if (compilation_type != Script::COMPILATION_TYPE_EVAL) {
    return HEAP->undefined_value();
  }


  Handle<Code> code(SharedFunctionInfo::cast(
      script->eval_from_shared())->code());
  return Smi::FromInt(code->SourcePosition(code->instruction_start() +
                      script->eval_from_instructions_offset()->value()));
}

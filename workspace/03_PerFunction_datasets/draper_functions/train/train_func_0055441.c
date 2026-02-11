TryGetCode() {
  Code* code;
  if (!FindCodeInCache(&code)) {

    MacroAssembler masm(NULL, 256);
    GenerateCode(&masm);


    CodeDesc desc;
    masm.GetCode(&desc);


    Code::Flags flags = Code::ComputeFlags(
        static_cast<Code::Kind>(GetCodeKind()),
        InLoop(),
        GetICState());
    Object* new_object;
    { MaybeObject* maybe_new_object =
          Heap::CreateCode(desc, flags, masm.CodeObject());
      if (!maybe_new_object->ToObject(&new_object)) return maybe_new_object;
    }
    code = Code::cast(new_object);
    RecordCodeGeneration(code, &masm);
    FinishCode(code);


    MaybeObject* maybe_new_object =
        Heap::code_stubs()->AtNumberPut(GetKey(), code);
    if (maybe_new_object->ToObject(&new_object)) {
      Heap::public_set_code_stubs(NumberDictionary::cast(new_object));
    }
  }

  return code;
}

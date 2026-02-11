GetCode() {
  Code* code;
  if (!FindCodeInCache(&code)) {
    v8::HandleScope scope;


    MacroAssembler masm(NULL, 256);
    GenerateCode(&masm);


    CodeDesc desc;
    masm.GetCode(&desc);


    Code::Flags flags = Code::ComputeFlags(
        static_cast<Code::Kind>(GetCodeKind()),
        InLoop(),
        GetICState());
    Handle<Code> new_object = Factory::NewCode(desc, flags, masm.CodeObject());
    RecordCodeGeneration(*new_object, &masm);
    FinishCode(*new_object);


    Handle<NumberDictionary> dict =
        Factory::DictionaryAtNumberPut(
            Handle<NumberDictionary>(Heap::code_stubs()),
            GetKey(),
            new_object);
    Heap::public_set_code_stubs(*dict);

    code = *new_object;
  }

  return Handle<Code>(code);
}

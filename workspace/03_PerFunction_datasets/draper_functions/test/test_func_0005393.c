IrregexpExecOnce(Handle<JSRegExp> regexp,
                                                        Handle<String> subject,
                                                        int index,
                                                        Vector<int> output) {
  Handle<FixedArray> irregexp(FixedArray::cast(regexp->data()));

  ASSERT(index >= 0);
  ASSERT(index <= subject->length());
  ASSERT(subject->IsFlat());

#ifdef V8_NATIVE_REGEXP
  ASSERT(output.length() >=
      (IrregexpNumberOfCaptures(*irregexp) + 1) * 2);
  do {
    bool is_ascii = subject->IsAsciiRepresentation();
    Handle<Code> code(IrregexpNativeCode(*irregexp, is_ascii));
    NativeRegExpMacroAssembler::Result res =
        NativeRegExpMacroAssembler::Match(code,
                                          subject,
                                          output.start(),
                                          output.length(),
                                          index);
    if (res != NativeRegExpMacroAssembler::RETRY) {
      ASSERT(res != NativeRegExpMacroAssembler::EXCEPTION ||
             Top::has_pending_exception());
      STATIC_ASSERT(
          static_cast<int>(NativeRegExpMacroAssembler::SUCCESS) == RE_SUCCESS);
      STATIC_ASSERT(
          static_cast<int>(NativeRegExpMacroAssembler::FAILURE) == RE_FAILURE);
      STATIC_ASSERT(static_cast<int>(NativeRegExpMacroAssembler::EXCEPTION)
                    == RE_EXCEPTION);
      return static_cast<IrregexpResult>(res);
    }


    IrregexpPrepare(regexp, subject);
  } while (true);
  UNREACHABLE();
  return RE_EXCEPTION;
#else

  ASSERT(output.length() >= IrregexpNumberOfRegisters(*irregexp));
  bool is_ascii = subject->IsAsciiRepresentation();


  int* register_vector = output.start();
  int number_of_capture_registers =
      (IrregexpNumberOfCaptures(*irregexp) + 1) * 2;
  for (int i = number_of_capture_registers - 1; i >= 0; i--) {
    register_vector[i] = -1;
  }
  Handle<ByteArray> byte_codes(IrregexpByteCode(*irregexp, is_ascii));

  if (IrregexpInterpreter::Match(byte_codes,
                                 subject,
                                 register_vector,
                                 index)) {
    return RE_SUCCESS;
  }
  return RE_FAILURE;
#endif
}

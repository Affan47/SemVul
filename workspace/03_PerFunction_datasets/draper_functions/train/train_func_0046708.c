EmitReturnSequence() {
  Comment cmnt(masm_, "[ Return sequence");
  if (return_label_.is_bound()) {
    __ jmp(&return_label_);
  } else {
    __ bind(&return_label_);
    if (FLAG_trace) {
      __ push(rax);
      __ CallRuntime(Runtime::kTraceExit, 1);
    }
#ifdef DEBUG

    Label check_exit_codesize;
    masm_->bind(&check_exit_codesize);
#endif
    CodeGenerator::RecordPositions(masm_, function()->end_position() - 1);
    __ RecordJSReturn();


    __ movq(rsp, rbp);
    __ pop(rbp);

    int arguments_bytes = (info_->scope()->num_parameters() + 1) * kPointerSize;
    __ Ret(arguments_bytes, rcx);

#ifdef ENABLE_DEBUGGER_SUPPORT


    const int kPadding = Assembler::kJSReturnSequenceLength - 7;
    for (int i = 0; i < kPadding; ++i) {
      masm_->int3();
    }


    ASSERT(Assembler::kJSReturnSequenceLength <=
           masm_->SizeOfCodeGeneratedSince(&check_exit_codesize));
#endif
  }
}

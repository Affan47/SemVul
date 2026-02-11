ProcessDeferred() {
  while (!deferred_.is_empty()) {
    DeferredCode* code = deferred_.RemoveLast();
    ASSERT(masm_ == code->masm());

    masm_->positions_recorder()->RecordStatementPosition(
        code->statement_position());
    if (code->position() != RelocInfo::kNoPosition) {
      masm_->positions_recorder()->RecordPosition(code->position());
    }

    Comment cmnt(masm_, code->comment());
    masm_->bind(code->entry_label());
    if (code->AutoSaveAndRestore()) {
      code->SaveRegisters();
    }
    code->Generate();
    if (code->AutoSaveAndRestore()) {
      code->RestoreRegisters();
      code->Exit();
    }
  }
}

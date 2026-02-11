SetSourcePosition(int pos) {
  if (FLAG_debug_info && pos != RelocInfo::kNoPosition) {
    masm_->positions_recorder()->RecordPosition(pos);
  }
}

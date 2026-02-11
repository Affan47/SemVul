SlotAddress(JavaScriptFrame* frame, int slot_index) {
  if (slot_index >= 0) {
    const int offset = JavaScriptFrameConstants::kLocal0Offset;
    return frame->fp() + offset - (slot_index * kPointerSize);
  } else {
    const int offset = JavaScriptFrameConstants::kReceiverOffset;
    return frame->caller_sp() + offset + (slot_index * kPointerSize);
  }
}

execute() {
  reset_stack();
  FrameEditor* ed = (FrameEditor*)GetEditor();
  ComValue retval(ed->NumFrames());
  push_stack(retval);
}

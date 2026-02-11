SingletonFor(StackFrame::Type type) {
#define FRAME_TYPE_CASE(type, field) \
  case StackFrame::type: result = &field##_; break;

  StackFrame* result = NULL;
  switch (type) {
    case StackFrame::NONE: return NULL;
    STACK_FRAME_TYPE_LIST(FRAME_TYPE_CASE)
    default: break;
  }
  return result;

#undef FRAME_TYPE_CASE
}

GetCallerStackPointer() const {
  int arguments;
  if (Heap::gc_state() != Heap::NOT_IN_GC ||
      SafeStackFrameIterator::is_active()) {


    arguments = 0;
  } else {


    JSFunction* function = JSFunction::cast(this->function());
    arguments = function->shared()->formal_parameter_count() + 1;
  }
  const int offset = StandardFrameConstants::kCallerSPOffset;
  return fp() + offset + (arguments * kPointerSize);
}

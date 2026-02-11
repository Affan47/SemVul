Abort(const char* format, ...) {
  if (FLAG_trace_bailout) {
    SmartPointer<char> debug_name = graph()->debug_name()->ToCString();
    PrintF("Aborting LCodeGen in @\"%s\": ", *debug_name);
    va_list arguments;
    va_start(arguments, format);
    OS::VPrint(format, arguments);
    va_end(arguments);
    PrintF("\n");
  }
  status_ = ABORTED;
}

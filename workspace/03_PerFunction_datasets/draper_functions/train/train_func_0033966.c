WriteAscii(char* buffer,
                       int start,
                       int length,
                       WriteHints hints) const {
  if (IsDeadCheck("v8::String::WriteAscii()")) return 0;
  LOG_API("String::WriteAscii");
  ENTER_V8;
  ASSERT(start >= 0 && length >= -1);
  i::Handle<i::String> str = Utils::OpenHandle(this);
  StringTracker::RecordWrite(str);
  if (hints & HINT_MANY_WRITES_EXPECTED) {


    str->TryFlatten();
  }
  int end = length;
  if ( (length == -1) || (length > str->length() - start) )
    end = str->length() - start;
  if (end < 0) return 0;
  write_input_buffer.Reset(start, *str);
  int i;
  for (i = 0; i < end; i++) {
    char c = static_cast<char>(write_input_buffer.GetNext());
    if (c == '\0') c = ' ';
    buffer[i] = c;
  }
  if (length == -1 || i < length)
    buffer[i] = '\0';
  return i;
}

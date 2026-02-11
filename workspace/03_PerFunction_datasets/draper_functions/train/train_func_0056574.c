StackWalk(Vector<OS::StackFrame> frames) {

#ifdef __GLIBC__
  int frames_size = frames.length();
  ScopedVector<void*> addresses(frames_size);

  int frames_count = backtrace(addresses.start(), frames_size);

  char** symbols = backtrace_symbols(addresses.start(), frames_count);
  if (symbols == NULL) {
    return kStackWalkError;
  }

  for (int i = 0; i < frames_count; i++) {
    frames[i].address = addresses[i];


    SNPrintF(MutableCStrVector(frames[i].text, kStackWalkMaxTextLen),
             "%s",
             symbols[i]);

    frames[i].text[kStackWalkMaxTextLen - 1] = '\0';
  }

  free(symbols);

  return frames_count;
#else
  return 0;
#endif
}

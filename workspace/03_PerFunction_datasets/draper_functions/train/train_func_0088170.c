DumpStackFrameInfo(const char* prefix, void* pc) {

  const char *symbol = "(unknown)";
  char symbolized[1024];


  if (Symbolize(reinterpret_cast<char *>(pc) - 1,
                symbolized, sizeof(symbolized))) {
    symbol = symbolized;
  }

  char buf[1024];
  MinimalFormatter formatter(buf, sizeof(buf));

  formatter.AppendString(prefix);
  formatter.AppendString("@ ");
  const int width = 2 * sizeof(void*) + 2;
  formatter.AppendHexWithPadding(reinterpret_cast<uintptr_t>(pc), width);
  formatter.AppendString(" ");
  formatter.AppendString(symbol);
  formatter.AppendString("\n");
  g_failure_writer(buf, formatter.num_bytes_written());
}

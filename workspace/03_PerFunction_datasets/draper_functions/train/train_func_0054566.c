DumpPCAndSymbol(DebugWriter *writerfn, void *arg, void *pc,
                            const char * const prefix) {
  char tmp[1024];
  const char *symbol = "(unknown)";


  if (Symbolize(reinterpret_cast<char *>(pc) - 1, tmp, sizeof(tmp))) {
      symbol = tmp;
  }
  char buf[1024];
  snprintf(buf, sizeof(buf), "%s@ %*p  %s\n",
           prefix, kPrintfPointerFieldWidth, pc, symbol);
  writerfn(buf, arg);
}

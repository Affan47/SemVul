jsWarnAt(const char *message, struct JsLex *lex, size_t tokenPos) {
  jsiConsoleRemoveInputLine();
  jsiConsolePrint("WARNING: ");
  jsiConsolePrint(message);
  if (lex) {
    jsiConsolePrint(" at ");
    jsiConsolePrintPosition(lex, tokenPos);
  } else
    jsiConsolePrint("\n");
}

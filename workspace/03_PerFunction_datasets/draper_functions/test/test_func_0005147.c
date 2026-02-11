jsiHandleNewLine(bool execute) {
  if (jsiAtEndOfInputLine()) {
    if (execute && jsiCountBracketsInInput()<=0) {
      if (jsiShowInputLine()) {
        jsiConsolePrint("\n");
      }
      if (!(jsiStatus & JSIS_ECHO_OFF_FOR_LINE))
        inputLineRemoved = true;


      JsVar *lineToExecute = jsvStringTrimRight(inputLine);
      jsiInputLineCursorMoved();
      jsvUnLock(inputLine);
      inputLine = jsvNewFromEmptyString();
      inputCursorPos = 0;

      JsVar *v = jspEvaluateVar(lineToExecute, 0, false);

      jsiHistoryAddLine(lineToExecute);
      jsvUnLock(lineToExecute);

      if (jsiEcho() && !jspHasError()) {
        jsiConsolePrintChar('=');
        jsfPrintJSON(v, JSON_LIMIT | JSON_NEWLINES | JSON_PRETTY | JSON_SHOW_DEVICES);
        jsiConsolePrint("\n");
      }
      jsvUnLock(v);


      jsiStatus &= ~JSIS_ECHO_OFF_FOR_LINE;
    } else {


      if (jsiShowInputLine()) jsiConsolePrint("\n:");
      jsiIsAboutToEditInputLine();
      jsiAppendToInputLine("\n");
      inputCursorPos++;
    }
  } else {
    jsiIsAboutToEditInputLine();
    if (jsiShowInputLine()) jsiConsoleEraseStringVarFrom(inputLine, inputCursorPos, false);
    JsVar *v = jsvNewFromEmptyString();
    if (inputCursorPos>0) jsvAppendStringVar(v, inputLine, 0, inputCursorPos);
    jsvAppendCharacter(v, '\n');
    jsvAppendStringVar(v, inputLine, inputCursorPos, JSVAPPENDSTRINGVAR_MAXLENGTH);
    jsiInputLineCursorMoved();
    jsvUnLock(inputLine);
    inputLine=v;
    if (jsiShowInputLine()) {
      jsiConsolePrintStringVarWithNewLineChar(inputLine, inputCursorPos, ':');
      jsiMoveCursorChar(inputLine, jsvGetStringLength(inputLine), inputCursorPos+1);
    }
    inputCursorPos++;
  }
}

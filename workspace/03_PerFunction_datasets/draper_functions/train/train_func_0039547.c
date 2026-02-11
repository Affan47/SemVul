discardEscapeChar(TCHAR* input, TCHAR* output) {

  const size_t inputLen = _tcslen(input);
  bool outputOwned=false;
  if (output == NULL){

    output = _CL_NEWARRAY(TCHAR, inputLen + 1);
    outputOwned=true;
  }


  int32_t length = 0;


  bool lastCharWasEscapeChar = false;


  uint32_t codePointMultiplier = 0;


  int32_t codePoint = 0;

  for (size_t i = 0; i < inputLen; i++) {
    TCHAR curChar = input[i];
    if (codePointMultiplier > 0) {
		try {
			codePoint += hexToInt(curChar) * codePointMultiplier;
		} catch (CLuceneError& e) {
			if (outputOwned)_CLDELETE_LCARRAY(output);
			throw e;
		}
      codePointMultiplier = codePointMultiplier >> 4;
      if (codePointMultiplier == 0) {
        output[length++] = (TCHAR)codePoint;
        codePoint = 0;
      }
    } else if (lastCharWasEscapeChar) {
      if (curChar == _T('u')) {

        codePointMultiplier = 16 * 16 * 16;
      } else {

        output[length] = curChar;
        length++;
      }
      lastCharWasEscapeChar = false;
    } else {
      if (curChar == _T('\\')) {
        lastCharWasEscapeChar = true;
      } else {
        output[length] = curChar;
        length++;
      }
    }
  }

  if (codePointMultiplier > 0) {
    if (outputOwned)_CLDELETE_LCARRAY(output);
    _CLTHROWT(CL_ERR_Parse, _T("Truncated unicode escape sequence."));
  }

  if (lastCharWasEscapeChar) {
    if (outputOwned)_CLDELETE_LCARRAY(output);
    _CLTHROWT(CL_ERR_Parse,_T("Term can not end with escape character."));
  }

  output[length]=0;
  return output;
}

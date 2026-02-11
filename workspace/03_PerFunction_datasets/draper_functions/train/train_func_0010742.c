jswrap_espruino_nativeCall(JsVarInt addr, JsVar *signature, JsVar *data) {
  unsigned int argTypes = 0;
  if (jsvIsUndefined(signature)) {

  } else if (jsvIsString(signature)) {
    JsLex lex;
    jslInit(&lex, signature);
    int argType;
    bool ok = true;
    int argNumber = 0;
    argType = nativeCallGetCType(&lex);
    if (argType>=0) argTypes |= (unsigned)argType << (JSWAT_BITS * argNumber++);
    else ok = false;
    if (ok) ok = jslMatch(&lex, '(');
    while (ok && lex.tk!=LEX_EOF && lex.tk!=')') {
      argType = nativeCallGetCType(&lex);
      if (argType>=0) {
        argTypes |= (unsigned)argType << (JSWAT_BITS * argNumber++);
        if (lex.tk!=')') ok = jslMatch(&lex, ',');
      } else ok = false;
    }
    if (ok) ok = jslMatch(&lex, ')');
    jslKill(&lex);
    if (argTypes & (unsigned int)~0xFFFF)
      ok = false;
    if (!ok) {
      jsExceptionHere(JSET_ERROR, "Error Parsing signature at argument number %d", argNumber);
      return 0;
    }
  } else {
    jsExceptionHere(JSET_ERROR, "Invalid Signature");
    return 0;
  }

  JsVar *fn = jsvNewNativeFunction((void *)(size_t)addr, (unsigned short)argTypes);
  if (data) {
    JsVar *flat = jsvAsFlatString(data);
    jsvUnLock(jsvAddNamedChild(fn, flat, JSPARSE_FUNCTION_CODE_NAME));
    jsvUnLock(flat);
  }
  return fn;
}

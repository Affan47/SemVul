jswrap_function_constructor(JsVar *args) {
  JsVar *fn = jsvNewWithFlags(JSV_FUNCTION);
  if (!fn) return 0;


  JsvObjectIterator it;
  jsvObjectIteratorNew(&it, args);
  JsVar *v = jsvObjectIteratorGetValue(&it);
  jsvObjectIteratorNext(&it);
  while (jsvObjectIteratorHasValue(&it)) {
    JsVar *s = jsvAsString(v, false);
    if (s) {


      JsVar *paramName = jsvNewFromStringVar(s, 0, JSVAPPENDSTRINGVAR_MAXLENGTH);
      jsvUnLock(s);
      if (paramName) {
        jsvMakeFunctionParameter(paramName);
        jsvAddName(fn, paramName);
        jsvUnLock(paramName);
      }
    }

    jsvUnLock(v);
    v = jsvObjectIteratorGetValue(&it);
    jsvObjectIteratorNext(&it);
  }
  jsvObjectIteratorFree(&it);

  JsVar *codeStr = jsvVarPrintf("{\n%v\n}", v);
  jsvUnLock(v);
  jsvUnLock(jsvObjectSetChild(fn, JSPARSE_FUNCTION_CODE_NAME, codeStr));
  return fn;
}

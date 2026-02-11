jswrap_eval(JsVar *v) {
  if (!v) return 0;
  JsVar *s = jsvAsString(v, false);
  JsVar *result = jspEvaluateVar(s, execInfo.thisVar, false);
  jsvUnLock(s);
  return result;
}

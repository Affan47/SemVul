jswrap_json_parse_internal(JsLex *lex) {
  switch (lex->tk) {
    case LEX_R_TRUE:  jslGetNextToken(lex); return jsvNewFromBool(true);
    case LEX_R_FALSE: jslGetNextToken(lex); return jsvNewFromBool(false);
    case LEX_R_NULL:  jslGetNextToken(lex); return jsvNewWithFlags(JSV_NULL);
    case '-': {
      jslGetNextToken(lex);
      if (lex->tk!=LEX_INT && lex->tk!=LEX_FLOAT) return 0;
      JsVar *v = jswrap_json_parse_internal(lex);
      JsVar *zero = jsvNewFromInteger(0);
      JsVar *r = jsvMathsOp(zero, v, '-');
      jsvUnLock(v);
      jsvUnLock(zero);
      return r;
    }
    case LEX_INT: {
      long long v = stringToInt(jslGetTokenValueAsString(lex));
      jslGetNextToken(lex);
      return jsvNewFromLongInteger(v);
    }
    case LEX_FLOAT: {
      JsVarFloat v = stringToFloat(jslGetTokenValueAsString(lex));
      jslGetNextToken(lex);
      return jsvNewFromFloat(v);
    }
    case LEX_STR: {
      JsVar *a = jslGetTokenValueAsVar(lex);
      jslGetNextToken(lex);
      return a;
    }
    case '[': {
      JsVar *arr = jsvNewWithFlags(JSV_ARRAY); if (!arr) return 0;
      jslGetNextToken(lex);
      while (lex->tk != ']') {
        JsVar *value = jswrap_json_parse_internal(lex);
        if (!value ||
            (lex->tk!=']' && !jslMatch(lex, ','))) {
          jsvUnLock(value);
          jsvUnLock(arr);
          return 0;
        }
        jsvArrayPush(arr, value);
        jsvUnLock(value);
      }
      if (!jslMatch(lex, ']')) {
        jsvUnLock(arr);
        return 0;
      }
      return arr;
    }
    case '{': {
      JsVar *obj = jsvNewWithFlags(JSV_OBJECT); if (!obj) return 0;
      jslGetNextToken(lex);
      while (lex->tk == LEX_STR) {
        JsVar *key = jsvAsArrayIndexAndUnLock(jslGetTokenValueAsVar(lex));
        jslGetNextToken(lex);
        JsVar *value = 0;
        if (!jslMatch(lex, ':') ||
            !(value=jswrap_json_parse_internal(lex)) ||
            (lex->tk!='}' && !jslMatch(lex, ','))) {
          jsvUnLock(key);
          jsvUnLock(value);
          jsvUnLock(obj);
          return 0;
        }
        jsvAddName(obj, jsvMakeIntoVariableName(key, value));
        jsvUnLock(value);
        jsvUnLock(key);
      }
      if (!jslMatch(lex, '}')) {
        jsvUnLock(obj);
        return 0;
      }
      return obj;
    }
    default: return 0;
  }
}

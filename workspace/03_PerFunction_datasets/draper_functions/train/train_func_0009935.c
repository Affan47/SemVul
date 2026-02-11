jspeUnaryExpression() {
    if (execInfo.lex->tk=='!' || execInfo.lex->tk=='~' || execInfo.lex->tk=='-' || execInfo.lex->tk=='+') {
      short tk = execInfo.lex->tk;
      JSP_ASSERT_MATCH(tk);
      if (!JSP_SHOULD_EXECUTE) {
        return jspeUnaryExpression();
      }
      if (tk=='!') {
        return jsvNewFromBool(!jsvGetBoolAndUnLock(jsvSkipNameAndUnLock(jspeUnaryExpression())));
      } else if (tk=='~') {
        return jsvNewFromInteger(~jsvGetIntegerAndUnLock(jsvSkipNameAndUnLock(jspeUnaryExpression())));
      } else if (tk=='-') {
        return jsvNegateAndUnLock(jspeUnaryExpression());
      }  else if (tk=='+') {
        JsVar *v = jsvSkipNameAndUnLock(jspeUnaryExpression());
        JsVar *r = jsvAsNumber(v);
        jsvUnLock(v);
        return r;
      }
      assert(0);
      return 0;
    } else
      return jspePostfixExpression();
}

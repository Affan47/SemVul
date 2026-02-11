jspeStatementFunctionDecl() {
  JsVar *funcName = 0;
  JsVar *funcVar;
  JSP_ASSERT_MATCH(LEX_R_FUNCTION);

  bool actuallyCreateFunction = JSP_SHOULD_EXECUTE || ((execInfo.execute&EXEC_PARSE_FUNCTION_DECL)!=0);
  if (actuallyCreateFunction) {
    funcName = jsvMakeIntoVariableName(jslGetTokenValueAsVar(execInfo.lex), 0);
    if (!funcName) {
      jspSetError(false);
      return 0;
    }
  }
  JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(funcName), 0);
  funcVar = jspeFunctionDefinition(false);
  if (actuallyCreateFunction) {


    JsVar *existingName = jspeiFindNameOnTop(funcName, true);
    JsVar *existingFunc = jsvSkipName(existingName);
    if (jsvIsFunction(existingFunc)) {

      funcVar = jsvSkipNameAndUnLock(funcVar);
      jswrap_function_replaceWith(existingFunc, funcVar);
      jsvUnLock(funcVar);
      funcVar = existingName;
    } else {
      jspReplaceWith(existingName, funcVar);
      jsvUnLock(funcName);
      funcName = existingName;
    }
    jsvUnLock(existingFunc);

  }
  jsvUnLock(funcVar);
  return funcName;
}

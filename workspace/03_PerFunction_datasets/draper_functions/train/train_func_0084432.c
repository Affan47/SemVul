jspeFactorMember(JsVar *a, JsVar **parentResult) {

  JsVar *parent = 0;

  while (execInfo.lex->tk=='.' || execInfo.lex->tk=='[') {
      if (execInfo.lex->tk == '.') {
          JSP_ASSERT_MATCH('.');
          if (JSP_SHOULD_EXECUTE) {

            const char *name = jslGetTokenValueAsString(execInfo.lex);

            JsVar *aVar = jsvSkipName(a);
            JsVar *child = 0;
            if (aVar)
              child = jspGetNamedField(aVar, name, true);
            if (!child) {
              if (jsvHasChildren(aVar)) {


                JsVar *nameVar = jslGetTokenValueAsVar(execInfo.lex);
                child = jsvCreateNewChild(aVar, nameVar, 0);
                jsvUnLock(nameVar);
              } else {

                jsExceptionHere(JSET_ERROR, "Field or method \"%s\" does not already exist, and can't create it on %t", name, aVar);
              }
            }
            JSP_MATCH_WITH_CLEANUP_AND_RETURN(LEX_ID, jsvUnLock(parent);jsvUnLock(a);jsvUnLock(aVar);, child);

            jsvUnLock(parent);
            parent = aVar;
            jsvUnLock(a);
            a = child;
          } else {

            JSP_MATCH_WITH_RETURN(LEX_ID, a);
          }
      } else if (execInfo.lex->tk == '[') {
          JsVar *index;
          JSP_ASSERT_MATCH('[');
          index = jsvSkipNameAndUnLock(jspeAssignmentExpression());
          JSP_MATCH_WITH_CLEANUP_AND_RETURN(']', jsvUnLock(parent);jsvUnLock(index);, a);
          if (JSP_SHOULD_EXECUTE) {
            index = jsvAsArrayIndexAndUnLock(index);
            JsVar *aVar = jsvSkipName(a);
            JsVar *child = 0;
            if (aVar)
              child = jspGetVarNamedField(aVar, index, true);

            if (!child) {
              if (jsvHasChildren(aVar)) {


                child = jsvCreateNewChild(aVar, index, 0);
              } else {
                jsExceptionHere(JSET_ERROR, "Field or method %q does not already exist, and can't create it on %t", index, aVar);
              }
            }
            jsvUnLock(parent);
            parent = jsvLockAgainSafe(aVar);
            jsvUnLock(a);
            a = child;
            jsvUnLock(aVar);
          }
          jsvUnLock(index);
      } else {
        assert(0);
      }
  }

  if (parentResult) *parentResult = parent;
  else jsvUnLock(parent);
  return a;
}

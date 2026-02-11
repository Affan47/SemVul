jspeBlockOrStatement() {
    if (execInfo.lex->tk=='{')
       return jspeBlock();
    else {
       JsVar *v = jspeStatement();
       if (execInfo.lex->tk==';') JSP_ASSERT_MATCH(';');
       return v;
    }
}

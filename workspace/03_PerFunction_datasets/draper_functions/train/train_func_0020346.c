repeatLast() {
    if (isNull(yylval=getLastExpr())) {
	ERRMSG(row) "Cannot use %s without any previous input", repeatStr
	EEND;
    }
    return REPEAT;
}

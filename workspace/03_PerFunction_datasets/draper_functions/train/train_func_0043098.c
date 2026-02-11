InterpretDollar(JSContext *cx, jschar *dp, jschar *ep, ReplaceData &rdata,
                size_t *skip)
{
    JSRegExpStatics *res;
    jschar dc, *cp;
    uintN num, tmp;

    JS_ASSERT(*dp == '$');


    if (dp + 1 >= ep)
        return NULL;


    res = &cx->regExpStatics;
    dc = dp[1];
    if (JS7_ISDEC(dc)) {

        num = JS7_UNDEC(dc);
        if (num > res->parenCount)
            return NULL;

        cp = dp + 2;
        if (cp < ep && (dc = *cp, JS7_ISDEC(dc))) {
            tmp = 10 * num + JS7_UNDEC(dc);
            if (tmp <= res->parenCount) {
                cp++;
                num = tmp;
            }
        }
        if (num == 0)
            return NULL;


        num--;
        *skip = cp - dp;
        return REGEXP_PAREN_SUBSTRING(res, num);
    }

    *skip = 2;
    switch (dc) {
      case '$':
        rdata.dollarStr.chars = dp;
        rdata.dollarStr.length = 1;
        return &rdata.dollarStr;
      case '&':
        return &res->lastMatch;
      case '+':
        return &res->lastParen;
      case '`':
        return &res->leftContext;
      case '\'':
        return &res->rightContext;
    }
    return NULL;
}
